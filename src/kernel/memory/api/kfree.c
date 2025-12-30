/*
** DELOS PROJECT, 2025
** src/kernel/memory/api/kfree
** File description:
** kfree source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Free data allocated from kmalloc.
 *
 * @param ptr    The pointer to the data allocated to be freed
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfree(void *ptr)
{
    kmalloc_header_t *header = NULL;

    if (ptr == NULL || (uint32_t) ptr < (uint32_t) kernel_heap_base || (uint32_t) ptr > (uint32_t) kernel_heap_brk) {
        return KO_FALSE;
    }
    header = KMALLOC_GO_BEFORE_HEADER(ptr);
    if (header->_free == OK_TRUE) {
        KPRINTF_ERROR("double free detected by trying to free %x", (uint32_t) ptr);
        return KO_FALSE;
    }
    header->_free = OK_TRUE;
    return OK_TRUE;
}
