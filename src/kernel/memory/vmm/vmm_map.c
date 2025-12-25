/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_map
** File description:
** VMM mapper source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <utils/kstdlib/kmemory.h>
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
kvmm_map_page(vaddr_t vaddr, paddr_t paddr, uint32_t flags)
{
    uint32_t pde_index = VMM_GET_PDE_INDEX(vaddr);
    uint32_t pte_index = VMM_GET_PTE_INDEX(vaddr);

    KPRINTF_DEBUG("PDE_i: %d", pde_index);
    KPRINTF_DEBUG("PTE_i: %d", pte_index);

    // Creating the page directory entry if not already present
    if (!kvmm_page_directory._entries[pde_index]._present) {
        page_table_entry_t *page_table = kpmm_alloc_pages(1); //TODO: add phys to virt macro
        kwmemset(page_table, 0, 4096);
        kvmm_page_directory._entries[pde_index]._present = OK_TRUE;
        kvmm_page_directory._entries[pde_index]._rw = OK_TRUE;
        kvmm_page_directory._entries[pde_index]._user = KO_FALSE;
        kvmm_page_directory._entries[pde_index]._table_addr = (uint32_t) page_table >> 12;
    }
    // Setup the page table entry in the page table we created
    page_table_entry_t *page_table = (void *) (kvmm_page_directory._entries[pde_index]._table_addr << 12); //TODO: add phys to virt macro
    page_table[pte_index]._present = OK_TRUE;
    page_table[pte_index]._rw = OK_TRUE;
    page_table[pte_index]._user = KO_FALSE;
    page_table[pte_index]._frame = paddr >> 12;

    // TODO: invalidate the TLB buffer
    KPRINTF_DEBUG("%x Vaddr mapped to %x Paddr", vaddr, paddr);
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

    KPRINTF_DEBUG("Freeing PDE_i: %d", pde_index);
    KPRINTF_DEBUG("Freeing PTE_i: %d", pte_index);
    if (!kvmm_page_directory._entries[pde_index]._present) {
        return KO_FALSE;
    }
    page_table_entry_t *page_table = (void *) (kvmm_page_directory._entries[pde_index]._table_addr << 12); //TODO: add phys to virt macro
    if (!page_table[pte_index]._present) {
        return KO_FALSE;
    }
    kwmemset(&page_table[pte_index], 0, 2);
    return OK_TRUE;
}
