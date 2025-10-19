/*
** DELOS PROJECT, 2025
** src/kernel/misc/panic
** File description:
** Panic source file
*/

#include "kernel/interruption/interruption.h"
#include "utils/kstdlib/kstring.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg           The optionnal message (can be NULL)
 */
void
kpanic(const char *msg)
{
    const char *kernel_panic_msg = "Kernel Panic!";
    const char *kernel_reason_msg = "This is the reason of the kernel panic:";
    const char *kernel_bottom_msg = "Please submit this to Del.";

    ktty_fill(' ', VGA_TEXT_PANIC_COLOR);
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_panic_msg) / 2), VGA_LINES_MAX / 2, kernel_panic_msg, VGA_TEXT_PANIC_COLOR);
    if (msg != NULL) {
        ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_reason_msg) / 2), (VGA_LINES_MAX / 2) + 1, kernel_reason_msg, VGA_TEXT_PANIC_COLOR);
        ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(msg) / 2), (VGA_LINES_MAX / 2) + 2, msg, VGA_TEXT_PANIC_COLOR);
    }
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_bottom_msg) / 2), VGA_LINES_MAX - 1, kernel_bottom_msg, VGA_TEXT_PANIC_COLOR);
    kstop_interruption();
    while (1);
}
