/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_bitmap
** File description:
** Physical memory manager bitmap source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/misc/panic.h>
#include <utils/misc/bitops.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>

/* @brief This variable is the pointer to the bitmap of pages for the PMM, allocated using early_allocator */
uint8_t *kpmm_bitmap = NULL;
uint32_t kpmm_bitmap_bytes_amout = 0;
uint32_t kpmm_pages_amount = 0;
uint32_t kpmm_free_pages_amount = 0;

/**
 * @brief Get the next bitmap concerning the next free page.
 *
 * @return The index of the bitmap concerning the next page.
 *         If you get 8 then it's the 8th bits in the kpmm_bitmap pointer to.
 */
uint64_t
kpmm_bitmap_get_next(void)
{
    int32_t bit_tmp = 0;

    if (kpmm_bitmap == NULL) {
        KPANIC("Trying to get the next bitmap with no bitmap allocated.");
        return KO_FALSE;
    }
    for (uint32_t i = 0; i < kpmm_bitmap_bytes_amout; i++) {
        bit_tmp = kbyte_has_free_bit(kpmm_bitmap[i]);
        if (bit_tmp >= 0) {
            return (i * 8) + bit_tmp;
        }
    }
    KPANIC("Didn't found any free bitmap bit.");
    return KO_FALSE;
}

/**
 * @brief Get the next bitmap concerning the next free page for n bitmap.
 *
 * @return The index of the bitmap concerning the next page.
 *         If you get 8 then it's the 8th bits in the kpmm_bitmap pointer to.
 */
uint64_t
kpmm_bitmap_get_n_continuous(uint32_t n)
{
    int32_t bit_tmp = 0;
    uint32_t current_continous = 0;

    if (kpmm_bitmap == NULL) {
        KPANIC("Trying to get the next bitmap with no bitmap allocated.");
        return KO_FALSE;
    }
    for (uint32_t i = 0; i < kpmm_bitmap_bytes_amout; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if ((kpmm_bitmap[i] & (1 << j)) == 0) {
                if (current_continous == 0) {
                    bit_tmp = (i * 8 + j);
                }
                current_continous++;
                if (current_continous >= n) {
                    return bit_tmp;
                }
            } else {
                current_continous = 0;
            }
        }
    }
    KPANIC("Didn't found any free space for N bitmap bit.");
    return KO_FALSE;
}

/**
 * @brief Get the physical address of the page of the bitmap index.
 *
 * @param bitmap_bit_i   The index of bitmap
 *
 * @return The pointer to the start of the page where the bitmap index linked to.
 */
inline void *
kpmm_bitmap_get_page_addr(uint64_t bitmap_bit_i)
{
    return ((void *) (uint32_t) (bitmap_bit_i * KERNEL_MEMORY_PMM_PAGE_SIZE));
}

/**
 * @brief Set the value on the bitmap index bit.
 *
 * @param bitmap_bit_i   The index of the bitmap bit
 * @param being_used     If true then used, false then free
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_bitmap_set_value(uint64_t bitmap_bit_i, bool32_t being_used)
{
    uint32_t byte_i = bitmap_bit_i / 8U;
    uint32_t bit_i = bitmap_bit_i % 8U;

    if (byte_i >= kpmm_bitmap_bytes_amout) {
        KPANIC("Trying to set the bitmap bit value to something while being not allocated.");
        return KO_FALSE;
    }
    if (being_used == OK_TRUE) {
        kpmm_bitmap[byte_i] |= 1 << bit_i;
    } else if (being_used == KO_FALSE) {
        kpmm_bitmap[byte_i] &= ~(1 << bit_i);
    } else {
        KPANIC("Trying to set the bitmap bit value to something differing true and false.");
        return KO_FALSE;
    }
    return OK_TRUE;
}
