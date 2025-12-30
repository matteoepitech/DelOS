/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_manager
** File description:
** VMM manager source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/arch/i386/interruption/idt.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <utils/kstdlib/kmemory.h>
#include <kernel/misc/panic.h>
#include <kernel/memory/mmu.h>
#include <kernel/memory/tlb.h>
#include <utils/asm/hlt.h>
#include <utils/misc/print.h>
#include <defines.h>

/* @brief The page directory content of the major content of the OS */
page_directory_t *kvmm_page_directory = NULL;

/**
 * @brief Allocate a page table using the early allocator with 4096 bytes alignment.
 *
 * @return The pointer to the allocated page table, NULL if allocation failed.
 */
static page_table_t *
alloc_page_table(void)
{
    page_table_t *pt = (page_table_t *) kearly_malloc_aligned(sizeof(page_table_t), 4096);

    if (pt == NULL) {
        return NULL;
    }
    kmemset((uint8_t *) pt, 0, sizeof(page_table_t));
    return pt;
}

/**
 * @brief Setup all entries of a page table to map 4MB of physical memory (0x00000000 - 0x003FFFFF).
 *        Each entry maps one page (4KB) with present, read/write, and supervisor flags.
 *
 * @param pt  The page table to setup
 */
static void
setup_page_table_entries(page_table_t *pt)
{
    uint32_t phys_addr = 0;

    for (uint32_t i = 0; i < 1024; i++) {
        phys_addr = i * 4096;
        pt->_entries[i]._present = 1;
        pt->_entries[i]._rw = 1;
        pt->_entries[i]._user = 0;
        pt->_entries[i]._frame = phys_addr >> 12;
    }
}

/**
 * @brief Setup a page directory entry to point to a page table.
 *
 * @param entry  The page directory entry to setup
 * @param pt     The page table to reference
 */
static void
setup_page_directory_entry(page_directory_entry_t *entry, page_table_t *pt)
{
    entry->_present = 1;
    entry->_rw = 1;
    entry->_user = 0;
    entry->_table_addr = (uint32_t) pt >> 12;
}

/**
 * @brief Setup identity mapping for the first 4MB of memory (0x00000000 - 0x003FFFFF).
 *        This mapping allows the kernel to continue executing after enabling paging.
 *
 * @param pd  The page directory
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
static bool32_t
setup_identity_mapping(page_directory_t *pd)
{
    page_table_t *identity_pt = alloc_page_table();

    if (identity_pt == NULL) {
        KPANIC_PHYS("Failed to allocate identity page table.");
        return KO_FALSE;
    }
    setup_page_table_entries(identity_pt);
    setup_page_directory_entry(&pd->_entries[0], identity_pt);
    return OK_TRUE;
}

/**
 * @brief Setup higher half mapping for the kernel (0xC0000000 - 0xC03FFFFF -> 0x00000000 - 0x003FFFFF).
 *        This mapping allows the kernel to run at high virtual addresses.
 *
 * @param pd  The page directory
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
static bool32_t
setup_higher_half_mapping(page_directory_t *pd)
{
    page_table_t *higher_half_pt = alloc_page_table();
    uint32_t kernel_pd_index = KVMM_PD_INDEX;

    if (higher_half_pt == NULL) {
        KPANIC_PHYS("Failed to allocate higher half page table.");
        return KO_FALSE;
    }
    setup_page_table_entries(higher_half_pt);
    setup_page_directory_entry(&pd->_entries[kernel_pd_index], higher_half_pt);
    return OK_TRUE;
}

/**
 * @brief Setup the recursive mapping for the kernel page directory.
 *        That mean we can access the page directory after the paging enabled easily using this address.
 *
 * @param pd  The page directory
 *
 * @return OK_TRUE.
 */
static bool32_t
setup_recursive_mapping(page_directory_t *pd)
{
    pd->_entries[1023]._present = 1;
    pd->_entries[1023]._rw = 1;
    pd->_entries[1023]._user = 0;
    pd->_entries[1023]._table_addr = (uint32_t) pd >> 12;
    return OK_TRUE;
}

/**
 * @brief Init the VMM manager with the page directory.
 *        Creates identity mapping (0x00000000 - 0x003FFFFF) and higher half mapping (0xC0000000 - 0xC03FFFFF).
 *        Loads the page directory into CR3 and enables paging.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
__attribute__((used)) bool32_t
kvmm_init(void)
{
    page_directory_t **pd_ptr = (page_directory_t **) VIRT_TO_PHYS(&kvmm_page_directory);

    *pd_ptr = (page_directory_t *) kearly_malloc_aligned(sizeof(page_directory_t), 4096);
    if (*pd_ptr == NULL) {
        KPANIC_PHYS("Failed to allocate page directory.");
        return KO_FALSE;
    }
    kmemset((uint8_t *) *pd_ptr, 0, sizeof(page_directory_t));
    if (setup_identity_mapping(*pd_ptr) == KO_FALSE) {
        return KO_FALSE;
    }
    if (setup_higher_half_mapping(*pd_ptr) == KO_FALSE) {
        return KO_FALSE;
    }
    setup_recursive_mapping(*pd_ptr);
    kmmu_load_cr3((paddr_t) *pd_ptr);
    kmmu_enable_paging();
    return OK_TRUE;
}

/**
 * @brief Disable the identity mapping to use the new CR3 which is the base one.
 *        Address which is virtual and physical at the same time will now be invalidated.
 *
 *        This is setting back the variable global to the virtual address
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_disable_identity_mapping(void)
{
    page_directory_t *pd = (page_directory_t *) 0xFFFFF000;
    paddr_t pd_phys_temp = (paddr_t) kvmm_page_directory;

    kpmm_bitmap = (uint8_t *) PHYS_TO_VIRT(kpmm_bitmap);
    kernel_early_heap_start = (uint8_t *) PHYS_TO_VIRT(kernel_early_heap_start);
    kernel_early_heap_end = (uint8_t *) PHYS_TO_VIRT(kernel_early_heap_end);
    kvmm_page_directory = (page_directory_t *) PHYS_TO_VIRT(kvmm_page_directory);
    pd->_entries[0]._present = 0;
    kmmu_load_cr3(pd_phys_temp);
    return OK_TRUE;
}
