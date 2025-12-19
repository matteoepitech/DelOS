/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_alloc
** File description:
** early allocator source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <utils/misc/print.h>
#include <defines.h>

/*
 * @brief Actual variables to manage the pointer of the start and end of early.
 */
uint8_t *kernel_early_heap_start = NULL;
uint8_t *kernel_early_heap_end = NULL;

/**
 * @brief Init the cursors for start and end of the early_allocator.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kearly_malloc_init(void)
{
    kernel_early_heap_start = (uint8_t *) &_kernel_early_heap_start_sym;
    kernel_early_heap_end = KERNEL_MEMORY_EARLY_DEFINE_END((uint8_t *) kernel_early_heap_start);
    if (kernel_early_heap_start == NULL || kernel_early_heap_end == NULL) {
        return KO_FALSE;
    }
    return OK_TRUE;
}

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
    void *ptr = NULL;

    if (bytes <= 0) {
        KPRINTF_ERROR("early_allocator: cannot allocate 0 byte");
        return ptr;
    }
    if (kernel_early_heap_start == NULL || kernel_early_heap_end == NULL) {
        KPRINTF_ERROR("early_allocator: bad cursors (NULL cursors)");
        return ptr;
    }
    if (kernel_early_heap_start + bytes > kernel_early_heap_end) {
        KPRINTF_ERROR("early_allocator: maximum memory reached");
        return ptr;
    }
    ptr = kernel_early_heap_start;
    kernel_early_heap_start += bytes;
    return ptr;
}
