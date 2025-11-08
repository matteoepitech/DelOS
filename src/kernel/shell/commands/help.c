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
    KDEBUG_TTY("All available commands:\n");
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        KDEBUG_TTY("  - ");
        KDEBUG_TTY(shell_commands[i].command);
        KDEBUG_TTY("\n");
    }
    return KO_FALSE;
}
