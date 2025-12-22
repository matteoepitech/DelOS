/*
** DELOS PROJECT, 2025
** include/kernel/memory/pmm/pmm
** File description:
** Physical memory manager header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_PMM_H_
    #define KERNEL_MEMORY_PMM_H_

    #ifndef KERNEL_MEMORY_PMM_PAGE_SIZE
        #define KERNEL_MEMORY_PMM_PAGE_SIZE 4096
    #endif /* ifndef KERNEL_MEMORY_PMM_PAGE_SIZE */

    #ifndef KERNEL_MEMORY_PMM_START_ADDR
        #define KERNEL_MEMORY_PMM_START_ADDR 0x100000
    #endif /* ifndef KERNEL_MEMORY_PMM_START_ADDR */
   
    // WARN:This will be removed and be automatically calculated using the BIOS firmware interruptions
    #define RAM_MIB_AMOUNT 4

/*
 * @brief This symbol comes from the linker script which place it next to the end of the code space.
 *
 *        INFO: This is a symbol located at the start of the physical "heap" and can be used using &.
 */
//extern uint8_t _kernel_pmm_heap_start_sym;  INFO: This is not being used since we have a problem where the PMM start is below some MMIO.
//                                                  If we use it back we need to add it back in the linker script.

/* @brief This variable is the pointer to the bitmap of pages for the PMM, allocated using early_allocator */
extern uint8_t *kpmm_bitmap;
extern uint32_t kpmm_bitmap_bytes_amout;
extern uint32_t kpmm_pages_amount;

/**
 * @brief Init the PMM using the early_allocator and calculating amount of bitmaps needed.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_init(void);

/**
 * @brief Debug function to display PMM internal informations.
 *        This function does NOT allocate anything and does NOT modify the PMM state.
 *        It is only used to validate PMM assumptions during early boot.
 */
void
kpmm_dump(void);

/**
 * @brief Get the next bitmap concerning the next free page.
 *
 * @return The index of the bitmap concerning the next page.
 *         If you get 8 then it's the 8th bits in the kpmm_bitmap pointer to.
 */
uint64_t
kpmm_bitmap_get_next(void);

/**
 * @brief Get the next bitmap concerning the next free page for n bitmap.
 *
 * @return The index of the bitmap concerning the next page.
 *         If you get 8 then it's the 8th bits in the kpmm_bitmap pointer to.
 */
uint64_t
kpmm_bitmap_get_n_continuous(uint32_t n);


/**
 * @brief Get the physical address of the page of the bitmap index.
 *
 * @param bitmap_bit_i   The index of bitmap
 *
 * @return The pointer to the start of the page where the bitmap index linked to.
 */
void *
kpmm_bitmap_get_page_addr(uint64_t bitmap_bit_i);

/**
 * @brief Set the value on the bitmap index bit.
 *
 * @param bitmap_bit_i   The index of the bitmap bit
 * @param being_used     If true then used, false then free
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_bitmap_set_value(uint64_t bitmap_bit_i, bool32_t being_used);

/**
 * @brief Allocate some pages in the physical address space.
 *
 * @param page_count     The number of pages allocated
 *
 * @return The pointer to the start of all pages allocated.
 */
void *
kpmm_alloc_pages(uint32_t page_count);

/**
 * @brief Free some pages N times.
 *
 * @param page_ptr       The start of the pointer of pages
 * @param page_count     The count of pages we need to free since the ptr
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_free_pages(void *page_ptr, uint32_t page_count);

#endif /* ifndef KERNEL_MEMORY_PMM_H_ */
