/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_manager
** File description:
** VMM manager source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <utils/kstdlib/kmemory.h>
#include <kernel/misc/panic.h>
#include <kernel/memory/mmu.h>
#include <kernel/memory/tlb.h>
#include <utils/misc/print.h>
#include <defines.h>

/* @brief The page directory content of the major content of the OS */
__attribute__((aligned(4096))) page_directory_t kvmm_page_directory;

/* @brief The page directory content of the bootstrap kernel phase */
__attribute__((aligned(4096))) page_directory_t kvmm_boot_page_directory;

/* @brief The first page table content of the bootstrap kernel phase | NO need more IG ? */
__attribute__((aligned(4096))) page_table_t kvmm_boot_first_page_table;

/* @brief The array of pages for the kernel after identity mapping */
__attribute__((aligned(4096))) page_table_t kvmm_boot_pt_pool[BOOT_PT_POOL_SIZE];
static uint32_t kvmm_boot_pt_pool_index = 0;

/**
 * @brief Allocate a page table from the boot pool.
 *        This function is used ONLY during boot before paging is enabled.
 *
 * @return Pointer to the allocated page table, or NULL if pool exhausted.
 */
static page_table_t *
kvmm_boot_alloc_page_table(void)
{
    page_table_t *pt = NULL;

    if (kvmm_boot_pt_pool_index >= BOOT_PT_POOL_SIZE) {
        KPANIC("Boot page table pool exhausted!");
        return NULL;
    } 
    pt = &kvmm_boot_pt_pool[kvmm_boot_pt_pool_index++];
    kmemset(pt, 0, sizeof(page_table_t));
    return pt;
}

/**
 * @brief Map a range of virtual addresses to physical addresses during boot.
 *        This function is used ONLY during boot before paging is enabled.
 *        It accesses page tables via physical addresses directly.
 *        After boot, use kvmm_map_page() instead.
 *
 * @param pd      The page directory to map into (physical address).
 * @param vstart  The starting virtual address.
 * @param pstart  The starting physical address.
 * @param size    The size of the region to map in bytes.
 * @param flags   Mapping flags (unused for now).
 */
static void
kvmm_boot_map_range(page_directory_t *pd, vaddr_t vstart, paddr_t pstart, uint32_t size, UNUSED uint32_t flags)
{
    uint32_t num_pages = (size + 0xFFF) >> 12;
    
    for (uint32_t i = 0; i < num_pages; i++) {
        vaddr_t vaddr = vstart + (i << 12);
        paddr_t paddr = pstart + (i << 12);
        uint32_t pd_index = vaddr >> 22;
        uint32_t pt_index = (vaddr >> 12) & 0x3FF;

        if (!pd->_entries[pd_index]._present) {
            page_table_t *new_pt = kvmm_boot_alloc_page_table();
            paddr_t pt_phys = VIRT_TO_PHYS(new_pt);   

            if (new_pt == NULL) {
                KPANIC("Failed to allocate page table!");
            }

            pd->_entries[pd_index]._present = 1;
            pd->_entries[pd_index]._rw = 1;
            pd->_entries[pd_index]._table_addr = pt_phys >> 12;
        }
        paddr_t pt_phys = pd->_entries[pd_index]._table_addr << 12;
        page_table_t *pt = (page_table_t *)pt_phys;        

        pt->_entries[pt_index]._present = 1;
        pt->_entries[pt_index]._rw = 1;
        pt->_entries[pt_index]._frame = paddr >> 12;
    }
}

/**
 * @brief Init the vmm manager with the page directory.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
__attribute__((used)) bool32_t
kvmm_init(void)
{
    paddr_t boot_pd_phys = VIRT_TO_PHYS(&kvmm_boot_page_directory);
    paddr_t real_pd_phys = VIRT_TO_PHYS(&kvmm_page_directory); 
    page_directory_t *boot_pd = (page_directory_t *) boot_pd_phys;
    page_directory_t *real_pd = (page_directory_t *) real_pd_phys;
    uint32_t kernel_virt_start = (uint32_t) &__kernel_start;
    uint32_t kernel_virt_end = (uint32_t) &__kernel_end;
    uint32_t kernel_phys_start = (uint32_t) &__kernel_physical_start;
    uint32_t kernel_size = kernel_virt_end - kernel_virt_start;
    uint32_t kernel_pd_start = kernel_virt_start >> 22;
    uint32_t kernel_pd_end = (kernel_virt_end - 1) >> 22;

    kmemset(boot_pd, 0, sizeof(page_directory_t));
    kmemset(real_pd, 0, sizeof(page_directory_t));
    kvmm_boot_map_range(boot_pd, 0x00000000, 0x00000000, 0x400000, 0);
    kvmm_boot_map_range(boot_pd, kernel_virt_start, kernel_phys_start, kernel_size, 0);
    for (uint32_t i = kernel_pd_start; i <= kernel_pd_end; i++) {
        real_pd->_entries[i] = boot_pd->_entries[i];
    }
    real_pd->_entries[0] = boot_pd->_entries[0];
    boot_pd->_entries[1023]._present = 1;
    boot_pd->_entries[1023]._rw = 1;
    boot_pd->_entries[1023]._table_addr = boot_pd_phys >> 12;
    real_pd->_entries[1023]._present = 1;
    real_pd->_entries[1023]._rw = 1;
    real_pd->_entries[1023]._table_addr = real_pd_phys >> 12;
    kmmu_load_cr3(boot_pd_phys);
    kmmu_enable_paging();
    return OK_TRUE;
}

/**
 * @brief Disable the identity mapping to use the new CR3 which is the base one.
 *        Address which is virtual and physical at the same time will now be invalidated.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_disable_identity_mapping(void)
{
    paddr_t page_dir_phys = VIRT_TO_PHYS(&kvmm_page_directory);

    kmmu_load_cr3(page_dir_phys);
    return OK_TRUE;
}
