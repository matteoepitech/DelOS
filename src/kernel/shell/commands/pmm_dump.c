/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/pmm_dump
** File description:
** pmm_dump command source file
*/

#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for pmm_dump.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_pmm_dump(UNUSED uint32_t argc, UNUSED char *argv[])
{
    e820_entry_t *entries = (e820_entry_t *) PHYS_TO_VIRT((uint32_t) KE820_INFO_VIRTUAL->_entries_buffer);

    if (kpmm_bitmap == NULL) {
        KPRINTF_ERROR("pmm dump: bitmap is NULL (initialization failed/missing)");
        return OK_TRUE;
    }
    KPRINTF_INFO("pmm dump: dump informations:");
    KPRINTF_INFO("  PMM page size            : %d bytes", KPMM_PAGE_SIZE);
    KPRINTF_INFO("  Total pages calculated   : %d", kpmm_pages_amount);
    KPRINTF_INFO("  Free pages amount        : %d/%d", (uint32_t) kpmm_free_pages_amount, (uint32_t) kpmm_pages_amount);
    KPRINTF_INFO("  Bitmap size allocated    : %d bytes", kpmm_bitmap_bytes_amout);
    KPRINTF_INFO("  Bitmap virtual address   : %p", kpmm_bitmap);
    KPRINTF_INFO("pmm dump: RAM regions from e820 BIOS: (%d)", KE820_INFO_VIRTUAL->_entries_count);
    for (uint32_t i = 0; i < KE820_INFO_VIRTUAL->_entries_count; i++) {
        KPRINTFN_INFO("  Addr %08x with length %08x | TYPE: ",
            (uint32_t) (entries[i]._base),
            (uint32_t) (entries[i]._length));
        switch (entries[i]._type) {
            case KE820_TYPE_FREE:
                kprintf(VGA_TEXT_SUCCESS_COLOR, "Free\n");
                break;
            case KE820_TYPE_USED:
                kprintf(VGA_TEXT_ERROR_COLOR, "Used\n");
                break;
            default:
                kprintf(VGA_TEXT_WARN_COLOR, "Other\n");
                break;
        }
    }
    return KO_FALSE;
}
