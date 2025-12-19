/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/clear
** File description:
** clear command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief Command for clear.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_clear(UNUSED uint32_t argc, UNUSED char *argv[])
{
    ktty_fill(' ', VGA_TEXT_DEFAULT_COLOR);
    ktty_cursor_set(0, 0);
    return KO_FALSE;
}
