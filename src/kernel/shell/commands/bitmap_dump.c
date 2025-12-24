/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/bitmap_dump
** File description:
** bitmap_dump command source file
*/

#include <kernel/memory/pmm/pmm.h>
#include <utils/kstdlib/kstdlib.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

#ifndef BITMAP_DUMP_MAX_ROW
    #define BITMAP_DUMP_MAX_ROW 64
#endif /* ifndef BITMAP_DUMP_MAX_ROW */

/**
 * @brief Print U(sed) or F(ree) for the bitmap bit state.
 *
 * @param val    The byte of the bitmap with the only bit to check.
 */
inline static void
print_bitmap_state(uint8_t val)
{
    if (val) {
        ktty_putc('U', VGA_TEXT_ERROR_COLOR);
    } else {
        ktty_putc('F', VGA_TEXT_SUCCESS_COLOR);
    }
}

/**
 * @brief Command for bitmap_dump.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_bitmap_dump(uint32_t argc, char *argv[])
{
    uint32_t size_remain = 0;
    uint32_t size_bytes = 0;
    int32_t size = 0;
    uint32_t tmp = 0;

    if (argc < 2) {
        KPRINTF_ERROR("%s", "usage: bitmapdump <size>");
        return OK_TRUE;
    }
    size = katoi(argv[1]);
    if (size <= 0) {
        KPRINTF_ERROR("%s", "bitmap_dump: the size must be greater than 0");
        return OK_TRUE;
    }
    size_bytes = size / 8U;
    size_remain = size % 8U;
    KPRINTF_DATE();
    for (uint32_t i = 0; i < size_bytes; i++) {
        for (uint32_t bit = 0; bit < 8; bit++) {
            if (tmp >= BITMAP_DUMP_MAX_ROW) {
                ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
                tmp = 0;
                KPRINTF_DATE();
            }
            print_bitmap_state(kpmm_bitmap[i] & (1 << bit));
            tmp++;
        }
    }
    for (uint32_t bit = 0; bit < size_remain; bit++) {
        if (tmp >= BITMAP_DUMP_MAX_ROW) {
            ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
            tmp = 0;
            KPRINTF_DATE();
        }
        print_bitmap_state(kpmm_bitmap[size_bytes] & (1 << bit));
        tmp++;
    }
    ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
    return KO_FALSE;
}
