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
#include <utils/misc/align.h>
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
kvmm_map_page(vaddr_t vaddr, paddr_t paddr, uint32_t flags)
{
    uint32_t pde_index = KVMM_GET_PDE_INDEX(vaddr);
    uint32_t pte_index = KVMM_GET_PTE_INDEX(vaddr);
    page_directory_t *pd = KVMM_GET_PD;
    page_table_t *page_table = NULL;
    paddr_t new_pt_phys = NULL;
    page_table_t *pt = NULL;

    if (!IS_ALIGNED_TO(vaddr, 4096) || !IS_ALIGNED_TO(paddr, 4096)) {
        KPRINTF_ERROR("Vaddr or Paddr is not aligned to 4096 for mapping");
        return KO_FALSE;
    }
    // Creating the page table entry if not already present
    if (pd->_entries[pde_index]._present == KO_FALSE) {
        new_pt_phys = (uint32_t) kpmm_alloc_pages(1);
        if (new_pt_phys == 0x0) {
            return KO_FALSE;
        }
        page_table = (page_table_t *) PHYS_TO_VIRT(new_pt_phys);
        kmemset(page_table, 0, 4096);
        pd->_entries[pde_index]._present = flags & KVMM_FLAG_PRESENT ? OK_TRUE : KO_FALSE;
        pd->_entries[pde_index]._rw = flags & KVMM_FLAG_RW ? OK_TRUE : KO_FALSE;
        pd->_entries[pde_index]._user = flags & KVMM_FLAG_USER ? OK_TRUE : KO_FALSE;
        pd->_entries[pde_index]._table_addr = new_pt_phys >> 12;
    }
    pt = KVMM_GET_PT_VIA_PDE(pde_index);
    // Setup the page table entry in the page table we created
    if (pt->_entries[pte_index]._present == OK_TRUE) {
        return KO_FALSE;
    }
    pt->_entries[pte_index]._present = flags & KVMM_FLAG_PRESENT ? OK_TRUE : KO_FALSE;
    pt->_entries[pte_index]._rw = flags & KVMM_FLAG_RW ? OK_TRUE : KO_FALSE;
    pt->_entries[pte_index]._user = flags & KVMM_FLAG_USER ? OK_TRUE : KO_FALSE;
    pt->_entries[pte_index]._frame = paddr >> 12;
    ktlb_invalidate((void *) vaddr);
    return OK_TRUE;
}

/**
 * @brief Map a virtual address to a physical address but in range.
 *        The physical address need to be in a linear way.
 *
 * @param vaddr  The virtual address
 * @param paddr  The physical address
 * @param flags  Some flags
 * @param amount The amount of page of size KPMM_PAGE_SIZE to alloc in range
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_map_range(vaddr_t vaddr, paddr_t paddr, uint32_t flags, uint32_t amount)
{
    if (!IS_ALIGNED_TO(vaddr, 4096) || !IS_ALIGNED_TO(paddr, 4096)) {
        KPRINTF_ERROR("Vaddr or Paddr is not aligned to 4096 for mapping");
        return KO_FALSE;
    }
    for (uint32_t i = 0; i < amount; i++) {
        if (kvmm_map_page(vaddr + (KPMM_PAGE_SIZE * i), paddr + (KPMM_PAGE_SIZE * i), flags) == KO_FALSE) {
            return KO_FALSE;
        }
    }
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
    uint32_t pde_index = KVMM_GET_PDE_INDEX(vaddr);
    uint32_t pte_index = KVMM_GET_PTE_INDEX(vaddr);
    page_table_t *page_table = NULL;

    if (!IS_ALIGNED_TO(vaddr, 4096)) {
        KPRINTF_ERROR("Vaddr is not aligned to 4096 for unmapping");
        return KO_FALSE;
    }
    if (KVMM_GET_PD->_entries[pde_index]._present == KO_FALSE) {
        return KO_FALSE;
    }
    page_table = KVMM_GET_PT_VIA_PDE(pde_index);
    if (page_table->_entries[pte_index]._present == KO_FALSE) {
        return KO_FALSE;
    }
    kwmemset(&page_table->_entries[pte_index], 0, 2);
    ktlb_invalidate((void *) vaddr);
    return OK_TRUE;
}
