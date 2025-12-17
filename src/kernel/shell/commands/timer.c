/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/timer
** File description:
** timer command source file
*/

#include "kernel/arch/i386/interruption/pit.h"
#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Command for timer.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_timer(UNUSED int argc, UNUSED char *argv[])
{
    ktty_puts("Timer informations:\n", VGA_TEXT_DEFAULT_COLOR);
    kprintf(VGA_TEXT_DEFAULT_COLOR, "  - Ticks count = %d\n  - Seconds count = %d\n", ticks_count, seconds_count);
    return KO_FALSE;
}
