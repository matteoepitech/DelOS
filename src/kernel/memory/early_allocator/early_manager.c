/*
** DELOS PROJECT, 2025
** src/kernel/memory/early_allocator/early_manager
** File description:
** early manage source file (bump allocator)
*/

#include <kernel/memory/early_allocator/early_alloc.h>
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
bool32_t
kearly_malloc_init(void)
{
    if (kernel_early_heap_available == KO_FALSE) {
        KPANIC("The early allocator is already disabled. Something tried to enable it.");
        return KO_FALSE;
    }
    if (kernel_early_heap_start != NULL && kernel_early_heap_end != NULL) {
        KPRINTF_ERROR("early_allocator: cursors are already initialized");
        return KO_FALSE;
    }
    kernel_early_heap_start = (uint8_t *) &_kernel_early_heap_start_sym;
    kernel_early_heap_end = KERNEL_MEMORY_EARLY_DEFINE_END((uint8_t *) kernel_early_heap_start);
    if (kernel_early_heap_start == NULL || kernel_early_heap_end == NULL) {
        return KO_FALSE;
    }
    if (kernel_early_heap_end <= kernel_early_heap_start) {
        KPANIC("Early allocator tried to be initialized but got bad cursors.");
        return KO_FALSE;
    }
    KPRINTF_OK("early_allocator: initialization done (%d KiB)", KERNEL_MEMORY_EARLY_SIZE / 1024);
    return OK_TRUE;
}

/**
 * @brief Disable the early allocator usage.
 *        WARN: After using this function the allocation will never be allowed using this allocator.
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
