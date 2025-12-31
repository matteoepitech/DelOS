/*
** DELOS PROJECT, 2025
** src/kernel/memory/api/krealloc
** File description:
** Krealloc source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kmemory.h>

/**
 * @brief Realloc a zone of data into a new one with a different size.
 *
 * @param ptr    The pointer to get data from and free
 * @param size   The size of the new allocation
 *
 * @return The new pointer reallocated.
 */
void *
krealloc(void *ptr, size_t size)
{
    kmalloc_header_t *header = NULL;
    uint8_t *new_ptr = NULL;

    if (ptr == NULL) {
        return NULL;
    }
    if (size == 0) {
        header = KMALLOC_GO_BEFORE_HEADER(ptr);
        size = header->_size;
    }
    new_ptr = kmalloc(size);
    kmemcpy(new_ptr, ptr, size);
    kfree(ptr);
    return new_ptr;
}
