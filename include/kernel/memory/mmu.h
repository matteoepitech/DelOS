/*
** DELOS PROJECT, 2025
** include/kernel/memory/mmu
** File description:
** MMU header file
*/

#include <kernel/memory/vmm/vmm.h>
#include <types.h>

#ifndef KERNEL_MEMORY_MMU_H_
    #define KERNEL_MEMORY_MMU_H_

/**
 * @brief Load the CR3 register with the physical address of the page directory start entries start.
 *
 * @param paddr   The physical address of the page directory to load on the CR3
 */
static inline void
kmmu_load_cr3(paddr_t paddr)
{
    // AT&T syntax used by GCC
    // mov source, destination
    __asm__ volatile("mov %0, %%cr3" :: "r"(paddr));
}

/**
 * @brief Read CR2 register (faulting virtual address).
 *
 * @return The virtual address stored in CR2.
 */
static inline vaddr_t
kmmu_get_cr2(void)
{
    vaddr_t val = 0;

    // AT&T syntax used by GCC
    // mov source, destination
    __asm__ volatile("mov %%cr2, %0" : "=r"(val) :: "memory");
    return val;
}

/**
 * @brief Enable the paging on the MMU.
 *        The memory management unit is now doing the translation from virtual to physical.
 */
static inline void
kmmu_enable_paging(void)
{
    uint32_t cr0 = 0;

    // AT&T syntax used by GCC
    // mov source, destination
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));
}

#endif /* ifndef KERNEL_MEMORY_MMU_H_ */
