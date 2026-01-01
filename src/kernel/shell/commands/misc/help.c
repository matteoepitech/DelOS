/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/misc/help
** File description:
** help command source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Get the maximum length of command name.
 *        Used to make an alignement for the help message.
 *
 * @return The maximum length of the command name.
 */
static uint32_t
get_max_command_name_length(void)
{
    uint32_t max_len = 0;
    uint32_t len = 0;

    for (uint32_t i = 0; shell_commands[i]._command != NULL; i++) {
        len = kstrlen(shell_commands[i]._command);
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

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
    const char *cmd = NULL;
    const char *desc = NULL;
    uint32_t len = 0;
    uint32_t max_len = get_max_command_name_length();

    KPRINTF_INFO("%s", "Available commands:");
    for (uint32_t i = 0; shell_commands[i]._command != NULL; i++) {
        cmd = shell_commands[i]._command;
        desc = shell_commands[i]._desc;
        len = kstrlen(cmd);
        KPRINTF_DATE();
        ktty_puts("  ", VGA_TEXT_DEFAULT_COLOR);
        ktty_puts(cmd, VGA_TEXT_DEFAULT_COLOR);
        for (uint32_t s = len; s < max_len + 2; s++) {
            ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR);
        }
        if (desc != NULL) {
            ktty_puts(desc, VGA_TEXT_DEFAULT_COLOR);
        }
        ktty_putc('\n', VGA_TEXT_DEFAULT_COLOR);
    }
    return KO_FALSE;
}
