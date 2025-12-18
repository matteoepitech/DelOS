/*
** DELOS PROJECT, 2025
** src/kernel/shell/parser/autocomplete
** File description:
** Autcomplete shell parsing source file
*/

#include "kernel/shell/parser/autocomplete.h"
#include "utils/kstdlib/kstring.h"
#include "utils/misc/print.h"
#include "kernel/shell/shell.h"

/**
 * @brief Continue by searching the first occurence for the autocomplete.
 *        INFO: This is a basic autocomplete only working on root of the command.
 *              Just made for speed-up development workflow not for user usage.
 *
 * @param buffer     The start of the buffer to autocomplete (will be modified if found)
 * @param length     The length of the current buffer (will be modified if found)
 *
 * @return The ID of the command in the array of commands. -1 if not found.
 */
int32_t
kshell_parse_autocomplete(char *buffer, uint32_t *length)
{
    if (buffer == NULL || length == NULL || *length == 0) {
        return -1;
    }
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        if (kstrncmp(buffer, shell_commands[i].command, *length) == 0) {
            ktty_puts(&shell_commands[i].command[*length], VGA_TEXT_DEFAULT_COLOR);
            buffer[0] = '\0';
            kstrcat(buffer, shell_commands[i].command);
            *length = kstrlen(buffer);
            return i;
        }
    }
    return -1;
}
