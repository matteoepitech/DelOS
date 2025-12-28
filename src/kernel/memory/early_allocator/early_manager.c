/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_manager
** File description:
** early manage source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <defines.h>

/*
 * @brief Actual variables to manage the pointer of the start and end of early.
 */
uint8_t *kernel_early_heap_start = NULL;
uint8_t *kernel_early_heap_end = NULL;
bool32_t kernel_early_heap_available = OK_TRUE;

/**
 * @brief Init the cursors for start and end of the early_allocator.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
__attribute__((used)) bool32_t
kearly_malloc_init(void)
{
    bool32_t *available_ptr = (bool32_t *) VIRT_TO_PHYS(&kernel_early_heap_available);
    uint8_t **heap_start_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_start);
    uint8_t **heap_end_ptr = (uint8_t **) VIRT_TO_PHYS(&kernel_early_heap_end);

    if (*available_ptr == KO_FALSE) {
        KPANIC_PHYS("The early allocator is already disabled.");
        return KO_FALSE;
    }
    if (*heap_start_ptr != NULL && *heap_end_ptr != NULL) {
        KPANIC_PHYS("The early allocator cursors are NULL.");
        return KO_FALSE;
    }
    *heap_start_ptr = (uint8_t *) VIRT_TO_PHYS(&__kernel_early_heap_start);
    *heap_end_ptr = KERNEL_MEMORY_EARLY_DEFINE_END(*heap_start_ptr);
    if (*heap_end_ptr <= *heap_start_ptr) {
        KPANIC_PHYS("Early allocator: bad cursors.");
        return KO_FALSE;
    }
    return OK_TRUE;
}

/**
 * @brief Disable the early allocator usage.
 *        WARN: After using this function the allocation will never be allowed using this allocator.
 *              Assuming this function is called after the virtual memory setup only.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kearly_malloc_disable(void)
{
    if (kernel_early_heap_available == KO_FALSE) {
        KPRINTF_ERROR("early_allocator: already disabled, you cannot disable it");
        return KO_FALSE;
    }
    kernel_early_heap_available = KO_FALSE;
    return OK_TRUE;
}
