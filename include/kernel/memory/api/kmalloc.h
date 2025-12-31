/*
** DELOS PROJECT, 2025
** include/kernel/memory/api/kmalloc
** File description:
** kmalloc header file
*/

#include <defines.h>
#include <types.h>

#ifndef KERNEL_MEMORY_API_KMALLOC_H_
    #define KERNEL_MEMORY_API_KMALLOC_H_

    #ifndef KMALLOC_PAGE_SIZE
        #define KMALLOC_PAGE_SIZE 4096 
    #endif /* ifndef KMALLOC_PAGE_SIZE */

    #ifndef KMALLOC_GO_AFTER_HEADER
        #define KMALLOC_GO_AFTER_HEADER(header) ((kmalloc_header_t *) header + 1)
    #endif /* ifndef KMALLOC_GO_AFTER_HEADER */

    #ifndef KMALLOC_GO_BEFORE_HEADER
        #define KMALLOC_GO_BEFORE_HEADER(header) ((kmalloc_header_t *) header - 1)
    #endif /* ifndef KMALLOC_GO_BEFORE_HEADER */

/* @brief Variables from the linker script to describe the position of the heap in the RAM */
extern uint8_t __kernel_heap_start;
extern uint8_t __kernel_heap_end;

/* @brief Variables for managing the heap */
extern uint8_t *kernel_heap_base;               // The base of the heap in virtual space
extern uint8_t *kernel_heap_brk;                // The current pointer to the program break (similary to brk() in linux)
extern uint8_t *kernel_heap_limit;              // The end of the heap in virtual space (no more heap after that)
extern struct kmalloc_header_s *kernel_heap_lh; // The last created header for the linked list (lh = last header)

/*
 * @brief Header for a malloc data.
 *        - free = if the data block is free then OK_TRUE, KO_FALSE otherwise
 *        - size = the size of allocation
 *        - next = the next header data
 *
 *        This header is before the real data to make the free list easier.
 *        e.g. [HEADER_DATA] [DATA] ... [HEADER_DATA] [DATA] [HEADER_DATA] [DATA]
 *
 *        If you want to access the data only using a header you can do:
 *           &header + sizeof(kmalloc_header_t)
 */
typedef struct kmalloc_header_s {
    bool32_t _free;
    uint32_t _size;
    struct kmalloc_header_s *_next;
} kmalloc_header_t;

/**
 * @brief Initialize the heap for malloc stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kmalloc_init(void);

/**
 * @brief Allocate in the heap memory of the kernel an amount of bytes.
 *
 * @param size   The size in bytes of the data to be allocated (prefer aligned bytes by 8/16)
 *
 * @return The pointer to that data allocated on the kernel heap.
 */
void *
kmalloc(size_t size);

/**
 * @brief Realloc a zone of data into a new one with a different size.
 *
 * @param ptr    The pointer to get data from and free
 * @param size   The size of the new allocation
 *
 * @return The new pointer reallocated.
 */
void *
krealloc(void *ptr, size_t size);

/**
 * @brief Free data allocated from kmalloc.
 *
 * @param ptr    The pointer to the data allocated to be freed
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfree(void *ptr);

#endif /* ifndef KERNEL_MEMORY_API_KMALLOC_H_ */
