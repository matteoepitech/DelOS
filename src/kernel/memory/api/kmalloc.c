/*
** DELOS PROJECT, 2025
** src/kernel/memory/api/kmalloc
** File description:
** kmalloc source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <utils/misc/align.h>
#include <defines.h>

/**
 * @brief Try to find a free header in the heap section.
 *
 * @param size   The amount of bytes aligned to allocate
 *
 * @return The pointer to the first header found or NULL if not found.
 */
static kmalloc_header_t *
find_free_heap_header(uint32_t size)
{
    kmalloc_header_t *tmp_header = (kmalloc_header_t *) kernel_heap_base;

    while (tmp_header != NULL) {
        if (tmp_header->_free == OK_TRUE && tmp_header->_size >= size) {
            break;
        }
        tmp_header = tmp_header->_next;
    }
    return tmp_header;
}

/**
 * @brief Create an heap header using the size and return it.
 *        This function assume the VMM / PMM is activated of course since it's using them.
 *
 * @param size   The amount of bytes aligned to allocate
 *
 * @return The created the pointer to the heap header.
 */
static kmalloc_header_t *
create_heap_header(uint32_t size)
{
    kmalloc_header_t *header = (kmalloc_header_t *) kernel_heap_brk;
    paddr_t frame = NULL;

    if (size == 0) {
        return NULL;
    }
    frame = (paddr_t) kpmm_alloc_pages(1);
    if (frame == NULL) {
        return NULL;
    }
    if (kvmm_map_page((vaddr_t) header, frame, KVMM_FLAG_PRESENT | KVMM_FLAG_RW) == KO_FALSE) {
        return NULL;
    }
    header->_free = KO_FALSE;
    header->_size = KMALLOC_PAGE_SIZE - sizeof(kmalloc_header_t);
    header->_next = kernel_heap_lh;
    return header;
}

/**
 * @brief Allocate in the heap memory of the kernel an amount of bytes.
 *
 * @param size   The size in bytes of the data to be allocated (prefer aligned bytes by 8/16)
 *
 * @return The pointer to that data allocated on the kernel heap.
 */
void *
kmalloc(uint32_t size)
{
    kmalloc_header_t *header = NULL;

    if (size == 0) {
        return NULL;
    }
    size = ALIGN_UP(size, 8);
    header = find_free_heap_header(size);
    if (header == NULL) {
        KPRINTF_ERROR("Didn't found any space for the heap allocation..");
        KPRINTF_OK("Creating one...");
        return create_heap_header(size);
    } else {
        KPRINTF_OK("Found a space for the heap allocation...");
        header->_free = KO_FALSE;
        header->_size -= size;
        return KMALLOC_GO_AFTER_HEADER(header);
    }
    return NULL;
}
