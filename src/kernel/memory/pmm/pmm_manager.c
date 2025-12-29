/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_manager
** File description:
** Physical memory manager management source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/e820.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <utils/misc/align.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Free all "not used" page after the init of the e820.
 *        We use a system of base/end to free only "accurate" region.
 *        e.g.: since the 0x0 region to 0xXXX is type 1. But you don't want to write on 0x0.
 */
static void
pmm_free_pages_from_e820(void)
{
    uint8_t **bitmap_ptr = (uint8_t **) VIRT_TO_PHYS(&kpmm_bitmap);
    uint8_t *bitmap_phys = *bitmap_ptr;
    uint32_t *free_pages_ptr = (uint32_t *) VIRT_TO_PHYS(&kpmm_free_pages_amount);
    uint64_t min_free_phys = ALIGN_UP((uint32_t) &__kernel_physical_end, KPMM_PAGE_SIZE);

    if (min_free_phys < KPMM_MIN_BASE) {
        min_free_phys = KPMM_MIN_BASE;
    }

    *free_pages_ptr = 0;
    for (uint32_t i = 0; i < KE820_INFO->_entries_count; i++) {
        if (KE820_INFO->_entries_buffer[i]._type == KE820_TYPE_FREE) {
            uint64_t base = KE820_INFO->_entries_buffer[i]._base;
            uint64_t length = KE820_INFO->_entries_buffer[i]._length;
            uint64_t region_start = base;
            uint64_t region_end = base + length;

            if (region_end <= min_free_phys) {
                continue;
            }
            if (region_start < min_free_phys) {
                region_start = min_free_phys;
            }
            uint64_t start_page = ALIGN_UP(region_start, KPMM_PAGE_SIZE) / KPMM_PAGE_SIZE;
            uint64_t end_page = ALIGN_DOWN(region_end, KPMM_PAGE_SIZE) / KPMM_PAGE_SIZE;

            if (end_page <= start_page) {
                continue;
            }
            for (uint64_t page = start_page; page < end_page; page++) {
                uint32_t byte_idx = page / 8;
                uint32_t bit_idx = page % 8;
                bitmap_phys[byte_idx] &= ~(1 << bit_idx);
                (*free_pages_ptr)++;
            }
        }
    }
}

/**
 * @brief Init the PMM using the early_allocator and calculating amount of bitmaps needed.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
__attribute__((used)) bool32_t
kpmm_init(void)
{
    uint32_t *pages_amount_ptr = (uint32_t *) VIRT_TO_PHYS(&kpmm_pages_amount);
    uint32_t *bitmap_bytes_ptr = (uint32_t *) VIRT_TO_PHYS(&kpmm_bitmap_bytes_amout);
    uint8_t **bitmap_ptr = (uint8_t **) VIRT_TO_PHYS(&kpmm_bitmap);
    uint8_t *bitmap_phys = NULL;
    uint64_t max_phys = 0;

    for (uint32_t i = 0; i < KE820_INFO->_entries_count; i++) {
        uint64_t end = KE820_INFO->_entries_buffer[i]._base + KE820_INFO->_entries_buffer[i]._length;
        if (end > max_phys) {
            max_phys = end;
        }
    }
    *pages_amount_ptr = ALIGN_UP(max_phys, KPMM_PAGE_SIZE) / KPMM_PAGE_SIZE;
    *bitmap_bytes_ptr = (*pages_amount_ptr + 7) / 8;
    *bitmap_ptr = kearly_malloc(*bitmap_bytes_ptr);
    if (*bitmap_ptr == NULL) {
        KPANIC_PHYS("PMM init failed: early allocator returned NULL.");
        return KO_FALSE;
    }
    bitmap_phys = *bitmap_ptr;
    for (uint32_t i = 0; i < *bitmap_bytes_ptr; i++) {
        bitmap_phys[i] = 0xFF;
    }
    pmm_free_pages_from_e820();
    return OK_TRUE;
}
