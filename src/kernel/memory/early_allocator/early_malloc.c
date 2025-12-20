/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_malloc
** File description:
** early malloc source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Basically a malloc() implementation for kernel purpose only in early stage.
 *        WARN: Only use this allocator for pre-stuff things.
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
    void *ptr = NULL;

    if (kernel_early_heap_available == KO_FALSE) {
        KPANIC("Early allocator tried to allocate memory while being disabled.");
        return ptr;
    }
    if (kernel_early_heap_start == NULL || kernel_early_heap_end == NULL) {
        KPANIC("Early allocator tried to allocate memory while using bad cursors.");
        return ptr;
    }
    if (bytes > (uint32_t) (kernel_early_heap_end - kernel_early_heap_start)) {
        KPRINTF_ERROR("early_allocator: maximum memory reached");
        return ptr;
    }
    if (bytes == 0) {
        KPRINTF_ERROR("early_allocator: cannot allocate 0 byte");
        return ptr;
    }
    ptr = kernel_early_heap_start;
    kernel_early_heap_start += bytes;
    return ptr;
}
