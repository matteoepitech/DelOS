/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_free
** File description:
** PMM free source file
*/

#include <kernel/memory/pmm/pmm.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Free some pages N times.
 *
 * @param page_ptr       The start of the pointer of pages
 * @param page_count     The count of pages we need to free since the ptr
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_free_pages(void *page_ptr, uint32_t page_count)
{
    uint64_t page_i = 0;

    if (page_count == 0) {
        return KO_FALSE;
    }
    page_i = (uint64_t) ((uint32_t) page_ptr - KERNEL_MEMORY_PMM_START_ADDR) / KERNEL_MEMORY_PMM_PAGE_SIZE;
    for (uint32_t i = 0; i < page_count; i++) {
        kpmm_bitmap_set_value(page_i + i, KO_FALSE);
    }
    return OK_TRUE;
}
