/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_map
** File description:
** VMM mapper source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <utils/kstdlib/kmemory.h>
#include <kernel/misc/panic.h>
#include <kernel/memory/tlb.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Map a virtual address to a physical address.
 *
 * @param vaddr  The virtual address
 * @param paddr  The physical address
 * @param flags  Some flags
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_map_page(vaddr_t vaddr, paddr_t paddr, UNUSED uint32_t flags)
{
    uint32_t pde_index = VMM_GET_PDE_INDEX(vaddr);
    uint32_t pte_index = VMM_GET_PTE_INDEX(vaddr);
    page_table_entry_t *page_table_entry = NULL;
    page_table_t *page_table = NULL;
    paddr_t new_pt_phys = NULL;

    // Creating the page table entry if not already present
    if (kvmm_page_directory->_entries[pde_index]._present == KO_FALSE) {
        new_pt_phys = (uint32_t) kpmm_alloc_pages(1);
        page_table = (page_table_t *) PHYS_TO_VIRT(new_pt_phys);
        if (new_pt_phys == 0x0) {
            return KO_FALSE;
        }
        kmemset(page_table, 0, 4096);
        kvmm_page_directory->_entries[pde_index]._present = OK_TRUE;
        kvmm_page_directory->_entries[pde_index]._rw = OK_TRUE;
        kvmm_page_directory->_entries[pde_index]._user = KO_FALSE;
        kvmm_page_directory->_entries[pde_index]._table_addr = new_pt_phys >> 12;
    }
    // Setup the page table entry in the page table we created
    page_table_entry = (void *) PHYS_TO_VIRT(kvmm_page_directory->_entries[pde_index]._table_addr << 12);
    if (page_table_entry[pte_index]._present == OK_TRUE) {
        return KO_FALSE;
    }
    page_table_entry[pte_index]._present = OK_TRUE;
    page_table_entry[pte_index]._rw = OK_TRUE;
    page_table_entry[pte_index]._user = KO_FALSE;
    page_table_entry[pte_index]._frame = paddr >> 12;
    ktlb_invalidate((void *) vaddr);
    return OK_TRUE;
}

/**
 * @brief Unmap a virtual address on the page table referenced by it's address.
 *
 * @param vaddr  The address to unmap
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_unmap_page(vaddr_t vaddr)
{
    uint32_t pde_index = VMM_GET_PDE_INDEX(vaddr);
    uint32_t pte_index = VMM_GET_PTE_INDEX(vaddr);
    page_table_entry_t *page_table = NULL;

    if (kvmm_page_directory->_entries[pde_index]._present == KO_FALSE) {
        return KO_FALSE;
    }
    page_table = (void *) PHYS_TO_VIRT(kvmm_page_directory->_entries[pde_index]._table_addr << 12);
    if (page_table[pte_index]._present == KO_FALSE) {
        return KO_FALSE;
    }
    kwmemset(&page_table[pte_index], 0, 2);
    ktlb_invalidate((void *) vaddr);
    return OK_TRUE;
}
