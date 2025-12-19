/*
** DELOS PROJECT, 2025
** include/kernel/shell/parser/autocomplete
** File description:
** Autocomplete header file
*/

#include <types.h>

#ifndef KERNEL_SHELL_PARSER_AUTOCOMPLETE_H_
    #define KERNEL_SHELL_PARSER_AUTOCOMPLETE_H_

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
kshell_parse_autocomplete(char *buffer, uint32_t *length);

#endif /* ifndef KERNEL_SHELL_PARSER_AUTOCOMPLETE_H_ */
