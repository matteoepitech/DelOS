/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_malloc
** File description:
** early malloc source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/vmm/vmm.h>
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
    bool32_t *available_ptr = (bool32_t *) VIRT_TO_PHYS(&kernel_early_heap_available);
    uint8_t **heap_start_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_start);
    uint8_t **heap_end_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_end);
    void *ptr = NULL;

    bytes = KERNEL_MEMORY_EARLY_ALIGN_UP(bytes);
    if (*available_ptr == KO_FALSE) {
        KPANIC("Early allocator tried to allocate memory while being disabled.");
        return ptr;
    }
    if (*heap_start_ptr == NULL || *heap_end_ptr == NULL) {
        KPANIC("Early allocator tried to allocate memory while using bad cursors.");
        return ptr;
    }
    if (bytes > (uint32_t) (*heap_end_ptr - *heap_start_ptr)) {
        KPRINTF_ERROR("early_allocator: maximum memory reached");
        return ptr;
    }
    if (bytes == 0) {
        KPRINTF_ERROR("early_allocator: cannot allocate 0 byte");
        return ptr;
    }
    ptr = *heap_start_ptr;
    *heap_start_ptr += bytes;
    return ptr;
}

/**
 * @brief Basically a malloc() implementation for kernel purpose only in early stage.
 *        Same version as kearly_malloc but with custom alignment.
 *
 * @param bytes  The number of bytes to allocate
 *
 * @return The pointer to the size memory allocated.
 */
void *
kearly_malloc_aligned(uint32_t bytes, uint32_t alignment)
{
    bool32_t *available_ptr = (bool32_t *) VIRT_TO_PHYS(&kernel_early_heap_available);
    uint8_t **heap_start_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_start);
    uint8_t **heap_end_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_end);
    uint32_t total_bytes = 0;
    uint32_t current = 0;
    uint32_t aligned = 0;
    void *ptr = NULL;

    if (*available_ptr == KO_FALSE) {
        KPANIC("Early allocator tried to allocate memory while being disabled.");
        return ptr;
    }
    if (*heap_start_ptr == NULL || *heap_end_ptr == NULL) {
        KPANIC("Early allocator tried to allocate memory while using bad cursors.");
        return ptr;
    }
    if (bytes == 0) {
        KPRINTF_ERROR("early_allocator: cannot allocate 0 byte");
        return ptr;
    }
    current = (uint32_t) *heap_start_ptr;
    aligned = (current + alignment - 1) & ~(alignment - 1);
    total_bytes = (aligned - current) + bytes;
    if (total_bytes > (uint32_t) (*heap_end_ptr - *heap_start_ptr)) {
        KPRINTF_ERROR("early_allocator: maximum memory reached");
        return ptr;
    }
    ptr = (void *) aligned;
    *heap_start_ptr = (uint8_t *) (aligned + bytes);
    return ptr;
}
