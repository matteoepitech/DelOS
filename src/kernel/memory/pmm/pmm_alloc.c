/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_alloc
** File description:
** PMM alloc source file
*/

#include <kernel/memory/pmm/pmm.h>
#include <defines.h>

/**
 * @brief Allocate some pages in the physical address space.
 *
 * @param page_count     The number of pages allocated
 *
 * @return The pointer to the start of all pages allocated.
 */
void *
kpmm_alloc_pages(uint32_t page_count)
{
    uint32_t bitmap_start = 0;

    if (page_count == 0) {
        return NULL;
    }
    bitmap_start = kpmm_bitmap_get_n_continuous(page_count);
    for (uint32_t i = 0; i < page_count; i++) {
        kpmm_bitmap_set_value(bitmap_start + i, OK_TRUE);
    }
    return kpmm_bitmap_get_page_addr(bitmap_start);
}
