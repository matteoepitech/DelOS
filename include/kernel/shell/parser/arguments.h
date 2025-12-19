/*
** DELOS PROJECT, 2025
** include/kernel/shell/parser/arguments
** File description:
** Argument header file
*/

#include <types.h>

#ifndef KERNEL_SHELL_PARSER_ARGUMENTS_H_
	#define KERNEL_SHELL_PARSER_ARGUMENTS_H_

	/* Number of ARGV that you can't overflow for parameters */
	#define SHELL_ARGV_MAX_COUNT 16

/**
 * @brief Check if a character is a delimiter or not for the parsing.
 *
 * @param c	 The character to check
 *
 * @return OK_TRUE if delimiter, KO_FALSE otherwise.
 */
bool32_t
kshell_parse_is_delimiter(const char c);

/**
 * @brief Format a buffer in this way "ls\0-l\0-a\0" for e.g.
 *
 * @param buffer	 The buffer to format
 */
void
kshell_parse_formatting_buffer(char *const buffer);

/**
 * @brief Get the number of arguments in the buffer, used in shell.
 *
 * @param buffer	 The buffer to check the number of argc
 *
 * @return The amount of the arguments in a buffer.
 */
uint32_t
kshell_parse_get_argc(const char *buffer);

/**
 * @brief Get the ARGV from the buffer, used in shell.
 *
 * @param buffer	 The buffer where the content is in this format : "ls\0-l\0-a\0"
 * @param argv  	 The ARGV array to be modified
 */
void kshell_parse_get_argv(char *buffer, char *argv[SHELL_ARGV_MAX_COUNT]);

#endif /* ifndef KERNEL_SHELL_PARSER_ARGUMENTS_H_ */
