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

/**
 * @brief Initialize the heap for malloc stuff.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kmalloc_init(void)
{
    paddr_t first_frame = (paddr_t) kpmm_alloc_pages(1);

    if (kvmm_map_page((vaddr_t) &__kernel_heap_start, first_frame, KVMM_FLAG_PRESENT | KVMM_FLAG_RW) == KO_FALSE) {
        KPANIC("Failure for malloc initialization while doing the virtual mapping.");
        return KO_FALSE;
    }
    KPRINTF_OK("malloc: intialization successful");
    return OK_TRUE;
}
