/*
** DELOS PROJECT, 2025
** include/kernel/misc/early_alloc
** File description:
** early_alloc header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_EARLY_ALLOCATOR_H_
    #define KERNEL_MEMORY_EARLY_ALLOCATOR_H_

    // INFO: This value (1024 * 1024) is arbitrary (4 KiB) and can be increased if needed and argumented
    #ifndef KERNEL_MEMORY_EARLY_SIZE
        #define KERNEL_MEMORY_EARLY_SIZE (1024 * 4)
    #endif /* ifndef KERNEL_MEMORY_EARLY_SIZE */

    #ifndef KERNEL_MEMORY_EARLY_DEFINE_END
        #define KERNEL_MEMORY_EARLY_DEFINE_END(start) (start + KERNEL_MEMORY_EARLY_SIZE)
    #endif /* ifndef KERNEL_MEMORY_EARLY_DEFINE_END */

/*
 * @brief This symbol comes from the linker script which place it next to the end of the code space.
 *        Basically: .text -> .rodata -> .data -> .bss -> _kernel_start_early_heap pointer
 *
 *        INFO: This is a symbol located at the start of the "heap" and can be used using &.
 */
extern uint8_t _kernel_early_heap_start_sym;

/*
 * @brief Actual variables to manage the pointer of the start and end of early.
 */
extern uint8_t *kernel_early_heap_start;
extern uint8_t *kernel_early_heap_end;

/*
 * @brief This variable is at OK_TRUE when init and KO_FALSE when disable.
 *        That means the usage of the bump allocator is usable or not.
 */
extern bool32_t kernel_early_heap_available;

/**
 * @brief Init the cursors for start and end of the early_allocator.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kearly_malloc_init(void);

/**
 * @brief Disable the early allocator usage.
 *        WARN: After using this function the allocation will never be allowed using this allocator.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kearly_malloc_disable(void);

/**
 * @brief Basically a malloc() implementation for kernel purpose only in early stage.
 *        WARN: Only use this allocator for pre-stuff things.
 *        INFO: This allocator is using a bump allocator / watermark algorithm.
 *              It contains a reference to the current ptr and just add the bytes to move.
 *              It not contains a free function since the size of the "heap" is "pre-used".
 *
 * @param bytes  The number of bytes to allocate
 *
 * @return The pointer to the size memory allocated.
 */
void *
kearly_malloc(uint32_t bytes);

#endif /* ifndef KERNEL_MEMORY_EARLY_ALLOCATOR_H_ */
