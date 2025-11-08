/*
** EPITECH PROJECT, 2025
** include/kernel/shell/shell
** File description:
** Shell header file
*/

#include "defines.h"
#include "types.h"

#ifndef KERNEL_SHELL_H_
    #define KERNEL_SHELL_H_

#define KERNEL_SHELL_BUFFER_SIZE 512

/**
 * @brief The shell command structure definition.
 */
typedef struct shell_command_s {
    char *command;
    uint8_t (*func)(int argc, char *argv[]);
} shell_command_t;

/**
 * @brief All shell commands.
 */
extern shell_command_t shell_commands[];

/**
 * @brief Start the shell and waiting for user prompt.
 *
 * @return OK_TRUE if worked KO_FALSE otherwise.
 */
bool32_t
kshell_start(void);

/*
 * -- COMMANDS --
 */

/**
 * @brief Command for reboot.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_reboot(UNUSED int argc, UNUSED char *argv[]);

/**
 * @brief Command for help.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_help(UNUSED int argc, UNUSED char *argv[]);

#endif /* ifndef KERNEL_SHELL_H_ */
