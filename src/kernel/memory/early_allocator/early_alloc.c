/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_alloc
** File description:
** early allocator source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <utils/misc/print.h>
#include <defines.h>

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
kearly_malloc(uint32_t bytes)
{
    if (bytes <= 0) {
        return NULL;
    }
    KPRINTF_DEBUG("%p", _kernel_start_early_heap);
    return NULL;
}
