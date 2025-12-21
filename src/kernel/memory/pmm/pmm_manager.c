/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_manager
** File description:
** Physical memory manager management source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>

/* @brief This variable is the pointer to the bitmap of pages for the PMM, allocated using early_allocator */
uint8_t *kpmm_bitmap = NULL;
uint32_t kpmm_bitmap_byte_amout = 0;
uint32_t kpmm_pages_amount = 0;

/**
 * @brief Init the PMM using the early_allocator and calculating amount of bitmaps needed.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_init(void)
{
    uint64_t ram_bytes = (uint64_t) RAM_MIB_AMOUNT * 1024ULL * 1024ULL; // WARN: will be removed see pmm.h for the reason

    kpmm_pages_amount = ram_bytes / KERNEL_MEMORY_PMM_PAGE_SIZE;
    kpmm_bitmap_byte_amout = (kpmm_pages_amount + 7) / 8;
    kpmm_bitmap = kearly_malloc(kpmm_bitmap_byte_amout);
    if (kpmm_bitmap == NULL) {
        KPANIC("The PMM failed to initialize due to the early allocator failure.");
        return KO_FALSE;
    }
    return OK_TRUE;
}

/**
 * @brief Debug function to display PMM internal informations.
 *        This function does NOT allocate anything and does NOT modify the PMM state.
 *        It is only used to validate PMM assumptions during early boot.
 */
void
kpmm_dump(void)
{
    uint64_t ram_bytes = (uint64_t) RAM_MIB_AMOUNT * 1024ULL * 1024ULL; // WARN: will be removed see pmm.h for the reason

    if (kpmm_bitmap == NULL) {
        KPRINTF_ERROR("pmm dump: bitmap is NULL (initialization failed/missing)");
        return;
    }
    KPRINTF_INFO("pmm dump: dump informations:");
    KPRINTF_INFO("  Reported RAM size        : %d bytes (%d MiB)", ram_bytes, RAM_MIB_AMOUNT);
    KPRINTF_INFO("  PMM page size            : %d bytes", KERNEL_MEMORY_PMM_PAGE_SIZE);
    KPRINTF_INFO("  Total pages calculated   : %d", kpmm_pages_amount);
    KPRINTF_INFO("  Bitmap size allocated    : %d bytes", kpmm_bitmap_byte_amout);
    KPRINTF_INFO("  Bitmap address           : %p", kpmm_bitmap);
}
