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
#include <defines.h>

/* @brief Variables for managing the heap */
uint8_t *kernel_heap_base = NULL;  // The base of the heap in virtual space
uint8_t *kernel_heap_brk = NULL;   // The current pointer to the program break (similary to brk() in linux)
uint8_t *kernel_heap_limit = NULL; // The end of the heap in virtual space (no more heap after that)

/**
 * @brief Initialize the heap for malloc stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kmalloc_init(void)
{
    paddr_t first_frame = (paddr_t) kpmm_alloc_pages(1);
    kmalloc_header_t *header = NULL;

    kernel_heap_base = &__kernel_heap_start;
    if (kvmm_map_page((vaddr_t) kernel_heap_base, first_frame, KVMM_FLAG_PRESENT | KVMM_FLAG_RW) == KO_FALSE) {
        KPANIC("Failure for malloc initialization while doing the virtual mapping.");
        return KO_FALSE;
    }
    header = (kmalloc_header_t *) kernel_heap_base;
    header->_free = OK_TRUE;
    header->_size = KMALLOC_PAGE_SIZE - sizeof(kmalloc_header_t);
    header->_next = NULL;
    kernel_heap_brk = kernel_heap_base + KMALLOC_PAGE_SIZE;
    kernel_heap_limit = (uint8_t *) &__kernel_heap_end;
    KPRINTF_OK("malloc: intialization successful");
    return OK_TRUE;
}
