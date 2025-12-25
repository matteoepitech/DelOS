/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_map
** File description:
** VMM mapper source file
*/

#include <kernel/memory/vmm/vmm.h>
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
    KPRINTF_DEBUG("%x Vaddr mapped to %x Paddr", vaddr, paddr);
    return OK_TRUE;
}
