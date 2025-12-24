/*
** DELOS PROJECT, 2025
** src/kernel/memory/pmm/pmm_manager
** File description:
** Physical memory manager management source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/memory/e820.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <utils/misc/align.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Free all "not used" page after the init of the e820.
 *        We use a system of base/end to free only "accurate" region.
 *        e.g.: since the 0x0 region to 0xXXX is type 1. But you don't want to write on 0x0.
 */
static void
pmm_free_pages_from_e820(void)
{
    uint64_t start_pfn = 0;
    uint64_t end_pfn = 0;
    uint64_t base = 0;
    uint64_t end = 0;

    for (uint32_t i = 0; i < E820_INFO->_entries_count; i++) {
        if (E820_INFO->_entries_buffer[i]._type != E820_TYPE_FREE)
            continue;
        base = E820_INFO->_entries_buffer[i]._base;
        end = base + E820_INFO->_entries_buffer[i]._length;
        if (end <= 0x100000)
            continue;
        if (base < 0x100000)
            base = 0x100000;
        base = ALIGN_UP(base, KERNEL_MEMORY_PMM_PAGE_SIZE);
        end = ALIGN_DOWN(end, KERNEL_MEMORY_PMM_PAGE_SIZE);
        if (base >= end)
            continue;
        start_pfn = base / KERNEL_MEMORY_PMM_PAGE_SIZE;
        end_pfn = end / KERNEL_MEMORY_PMM_PAGE_SIZE;
        for (uint64_t pfn = start_pfn; pfn < end_pfn; pfn++) {
            if (pfn == 0)
                continue;
            kpmm_bitmap_set_value(pfn, KO_FALSE);
            kpmm_free_pages_amount++;
        }
    }
}

/**
 * @brief Init the PMM using the early_allocator and calculating amount of bitmaps needed.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kpmm_init(void)
{
    uint64_t max_phys = 0;

    for (uint32_t i = 0; i < E820_INFO->_entries_count; i++) {
        uint64_t end = E820_INFO->_entries_buffer[i]._base + E820_INFO->_entries_buffer[i]._length;
        if (end > max_phys) {
            max_phys = end;
        }
    }
    kpmm_pages_amount = ALIGN_UP(max_phys, KERNEL_MEMORY_PMM_PAGE_SIZE) / KERNEL_MEMORY_PMM_PAGE_SIZE;
    kpmm_bitmap_bytes_amout = (kpmm_pages_amount + 7) / 8;
    kpmm_bitmap = kearly_malloc(kpmm_bitmap_bytes_amout);
    if (kpmm_bitmap == NULL) {
        KPANIC("PMM init failed: early allocator returned NULL.");
        return KO_FALSE;
    }
    for (uint64_t i = 0; i < kpmm_pages_amount; i++) {
        kpmm_bitmap_set_value(i, OK_TRUE);
    }
    pmm_free_pages_from_e820();
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
    if (kpmm_bitmap == NULL) {
        KPRINTF_ERROR("pmm dump: bitmap is NULL (initialization failed/missing)");
        return;
    }
    KPRINTF_INFO("pmm dump: dump informations:");
    KPRINTF_INFO("  PMM page size            : %d bytes", KERNEL_MEMORY_PMM_PAGE_SIZE);
    KPRINTF_INFO("  Total pages calculated   : %d", kpmm_pages_amount);
    KPRINTF_INFO("  Free pages amount        : %d/%d", (uint32_t) kpmm_free_pages_amount, (uint32_t) kpmm_pages_amount);
    KPRINTF_INFO("  Bitmap size allocated    : %d bytes", kpmm_bitmap_bytes_amout);
    KPRINTF_INFO("  Bitmap address           : %p", kpmm_bitmap);
    KPRINTF_INFO("pmm dump: RAM regions from e820 BIOS:");
    for (uint32_t i = 0; i < E820_INFO->_entries_count; i++) {
        KPRINTFN_INFO("  Addr %08x with length %08x | TYPE: ",
            (uint32_t) (E820_INFO->_entries_buffer[i]._base),
            (uint32_t) (E820_INFO->_entries_buffer[i]._length));
        switch (E820_INFO->_entries_buffer[i]._type) {
            case E820_TYPE_FREE:
                kprintf(VGA_TEXT_SUCCESS_COLOR, "Free\n");
                break;
            case E820_TYPE_USED:
                kprintf(VGA_TEXT_ERROR_COLOR, "Used\n");
                break;
            default:
                kprintf(VGA_TEXT_WARN_COLOR, "Other\n");
                break;
        }
    }
}
