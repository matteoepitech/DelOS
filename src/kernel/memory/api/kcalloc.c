/*
** DELOS PROJECT, 2026
** src/kernel/memory/api/kcalloc
** File description:
** Kcalloc source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kmemory.h>
#include <utils/misc/align.h>

/**
 * @brief Simple implementation of calloc (not count and size like usual calloc implementation).
 *
 * @param size   The number of bytes to allocate
 *
 * @return The pointer allocated in memory and filled by 0.
 */
void *
kcalloc(size_t size)
{
    void *ptr = NULL;

    if (size == 0) {
        return NULL;
    }
    ptr = kmalloc(size);
    kmemset(ptr, 0, ALIGN_UP(size, 8));
    return ptr;
}
