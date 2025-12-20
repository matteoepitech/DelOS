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
   
    // WARN:This will be removed and be automatically calculated using the BIOS firmware interruptions
    #define RAM_MIB_AMOUNT 4

/* @brief This variable is the pointer to the bitmap of pages for the PMM, allocated using early_allocator */
extern uint8_t *kpmm_bitmap;
extern uint32_t kpmm_bitmap_byte_amout;
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

#endif /* ifndef KERNEL_MEMORY_PMM_H_ */
