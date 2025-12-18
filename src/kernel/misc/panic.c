/*
** DELOS PROJECT, 2025
** src/kernel/misc/panic
** File description:
** Panic source file
*/

#include "kernel/arch/i386/interruption/interruption.h"
#include "utils/kstdlib/kstring.h"
#include "kernel/tty/tty.h"
#include "utils/asm/hlt.h"
#include "defines.h"

/**
 * @brief Format the location of the panic.
 *        TODO: Remove this function and replace it using a ksprintf function.
 *
 * @param buffer     Buffer to put the string to
 * @param file       The file string name
 * @param line       The line number
 */
static void
format_location(char *buffer, const char *file, uint32_t line)
{
    uint32_t i = 0;

    if (buffer == NULL || file == NULL) {
        return;
    }
    while (file[i] != '\0') {
        buffer[i] = file[i];
        i++;
    }
    buffer[i++] = ':';

    char temp[16];
    uint32_t j = 0;
    uint32_t num = line;

    if (num == 0) {
        temp[j++] = '0';
    } else {
        while (num > 0) {
            temp[j++] = '0' + (num % 10);
            num /= 10;
        }
    }

    for (uint32_t k = 0; k < j; k++) {
        buffer[i++] = temp[j - k - 1];
    }
    buffer[i] = '\0';
}


/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg    The optionnal message (can be NULL)
 * @param file   The file where the panic come from
 * @param line   The line where the panic come from
 */
void
kpanic(const char *msg, const char *file, uint32_t line)
{
    const char *kernel_panic_msg = "*** KERNEL PANIC ***";
    const char *kernel_reason_msg = "Reason:";
    const char *kernel_location_msg = "Location:";
    const char *kernel_bottom_msg = "System halted - Please submit this to Del";
    char line_buffer[128];

    file = file == NULL ? "(unknown)" : file;
    kinterruption_extern_stop();
    ktty_fill(' ', VGA_TEXT_PANIC_COLOR);
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_panic_msg) / 2),
                 VGA_LINES_MAX / 2 - 5,
                 kernel_panic_msg,
                 VGA_TEXT_PANIC_COLOR);
    if (msg != NULL) {
        ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_reason_msg) / 2),
                     VGA_LINES_MAX / 2 - 3,
                     kernel_reason_msg,
                     VGA_TEXT_PANIC_COLOR);
        ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(msg) / 2),
                     VGA_LINES_MAX / 2 - 2,
                     msg,
                     VGA_TEXT_PANIC_COLOR);
    }
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_location_msg) / 2),
                 VGA_LINES_MAX / 2 + 1,
                 kernel_location_msg,
                 VGA_TEXT_PANIC_COLOR);
    format_location(line_buffer, file, line);
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(line_buffer) / 2),
                 VGA_LINES_MAX / 2 + 2,
                 line_buffer,
                 VGA_TEXT_PANIC_COLOR);
    ktty_puts_at(VGA_COLUMNS_MAX / 2 - (kstrlen(kernel_bottom_msg) / 2),
                 VGA_LINES_MAX - 2,
                 kernel_bottom_msg,
                 VGA_TEXT_PANIC_COLOR);
    ktty_cursor_set_visibility(KO_FALSE);

    KHLT_HARD_DO_NO_MSG();
}
