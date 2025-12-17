/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/help
** File description:
** help command source file
*/

#include "kernel/shell/shell.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Command for help.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_help(UNUSED int argc, UNUSED char *argv[])
{
    ktty_puts("All available commands:\n", VGA_TEXT_DEFAULT_COLOR);
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        ktty_puts("  - ", VGA_TEXT_DEFAULT_COLOR);
        ktty_puts(shell_commands[i].command, VGA_TEXT_DEFAULT_COLOR);
        ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
    }
    return KO_FALSE;
}
