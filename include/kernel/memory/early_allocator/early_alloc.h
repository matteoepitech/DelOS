/*
** DELOS PROJECT, 2025
** include/kernel/misc/early_alloc
** File description:
** early_alloc header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_EARLY_ALLOCATOR_H_
    #define KERNEL_MEMORY_EARLY_ALLOCATOR_H_

/*
 * @brief This variable comes from the linker script which place it next to the end of the code space.
 *        Basically: .text -> .rodata -> .data -> .bss -> _kernel_start_early_heap pointer
 *
 *        INFO: This is an address which redirect to a byte.
 */
extern uint8_t _kernel_start_early_heap;

/**
 * @brief Basically a malloc() implementation for kernel purpose only in early stage.
 *        WARN: Do not use this allocator.
 *        INFO: This allocator is using a bump allocator / watermark algorithm.
 *              It contains a reference to the current ptr and just add the bytes to move.
 *              It not contains a free function since the size of the "heap" is "pre-used".
 *
 * @param bytes  The number of bytes to allocate
 *
 * @return The pointer to the size memory allocated.
 */
void *
kearly_malloc(uint32_t bytes);

#endif /* ifndef KERNEL_MEMORY_EARLY_ALLOCATOR_H_ */
