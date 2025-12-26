/*
** DELOS PROJECT, 2025
** include/kernel/memory/tlb
** File description:
** TLB header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_TLB_H_
    #define KERNEL_MEMORY_TLB_H_

/**
 * @brief Invalidate the TLB (translation lookaside buffer) for the MMU to perform a new
 *        cache registration for the virtual to physical address.
 */
static inline void
ktlb_invalidate(void *vaddr)
{
    // AT&T syntax used by GCC
    // mov source, destination
    __asm__ volatile("invlpg (%0)" : : "r"(vaddr) : "memory");
}

#endif /* ifndef KERNEL_MEMORY_TLB_H_ */
