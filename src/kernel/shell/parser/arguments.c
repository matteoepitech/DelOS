/*
** DELOS PROJECT, 2025
** src/kernel/shell/parser/arguments
** File description:
** Arguments shell parsing source file
*/

#include "kernel/shell/parser/arguments.h"
#include "utils/kstdlib/kmemory.h"
#include "utils/kstdlib/kstring.h"
#include "kernel/tty/tty.h"
#include "defines.h"
#include "types.h"

/**
 * @brief Check if a character is a delimiter or not for the parsing.
 *
 * @param c  The character to check
 *
 * @return OK_TRUE if delimiter, KO_FALSE otherwise.
 */
bool32_t
kshell_parse_is_delimiter(const char c)
{
    switch (c) {
        case '\t':
        case '\n':
        case ' ':
            return OK_TRUE;
        default:
            return KO_FALSE;
    }
    return KO_FALSE;
}

/**
 * @brief Format a buffer in this way "ls\0-l\0-a\0" for e.g.
 *
 * @param buffer     The buffer to format
 */
void
kshell_parse_formatting_buffer(char *const buffer)
{
    uint32_t jump_tmp = 0;

    if (buffer == NULL) {
        return;
    }
    for (uint32_t i = 0; buffer[i] != '\0'; i++) {
        while (!kshell_parse_is_delimiter(buffer[i]) && buffer[i] != '\0') {
            i++;
            continue;
        }
        buffer[i] = '\0';
        while (kshell_parse_is_delimiter(buffer[i + 1 + jump_tmp])) {
            jump_tmp++;
        }
        kmemmove(&buffer[i + 1], &buffer[i + 1 + jump_tmp], kstrlen(&buffer[i + 1 + jump_tmp]) + 1);
    }
}

/**
 * @brief Get the number of arguments in the buffer, used in shell.
 *
 * @param buffer     The buffer to check the number of argc
 *
 * @return The amount of the arguments in a buffer.
 */
uint32_t
kshell_parse_get_argc(const char *buffer)
{
    uint32_t argc_value = 0;

    if (buffer == NULL) {
        return 0;
    }
    for (bool32_t in_a_word = KO_FALSE; *buffer; buffer++) {
        while (kshell_parse_is_delimiter(*buffer)) {
            in_a_word = KO_FALSE;
            buffer++;
        }
        if (in_a_word == KO_FALSE && *buffer != '\0') {
            in_a_word = OK_TRUE;
            argc_value++;
        }
    }
    return argc_value;
}

/**
 * @brief Get the ARGV from the buffer, used in shell.
 *
 * @param buffer     The buffer where the content is in this format : "ls\0-l\0-a\0"
 * @param argv       The ARGV array to be modified
 */
void kshell_parse_get_argv(char *buffer, char *argv[SHELL_ARGV_MAX_COUNT])
{
    uint32_t index = 0;

    if (buffer == NULL || argv == NULL) {
        return;
    }
    for (bool32_t in_a_word = KO_FALSE; *buffer; buffer++) {
        while (kshell_parse_is_delimiter(*buffer)) {
            in_a_word = KO_FALSE;
            buffer++;
        }
        if (in_a_word == KO_FALSE && *buffer != '\0') {
            in_a_word = OK_TRUE;
            if (index >= SHELL_ARGV_MAX_COUNT)
                break;
            argv[index] = buffer;
            index++;
        }
    }
}
