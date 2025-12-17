/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/help
** File description:
** help command source file
*/

#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
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
kshell_help(UNUSED uint32_t argc, UNUSED char *argv[])
{
    KPRINTF_INFO("All available commands:");
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        KPRINTF_INFO("  - %s", shell_commands[i].command);
    }
    return KO_FALSE;
}
