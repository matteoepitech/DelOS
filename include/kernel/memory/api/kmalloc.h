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

/* @brief Variables from the linker script to describe the position of the heap in the RAM */
extern uint8_t __kernel_heap_start;
extern uint8_t __kernel_heap_end;

/*
 * @brief Header for a malloc data.
 *        - free = if the data block is free then OK_TRUE, KO_FALSE otherwise
 *        - size = the size of the data
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
    uint32_t *_size;
    struct kmalloc_header_s *_next;
} kmalloc_header_t;

/**
 * @brief Initialize the heap for malloc stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kmalloc_init(void);

#endif /* ifndef KERNEL_MEMORY_API_KMALLOC_H_ */
