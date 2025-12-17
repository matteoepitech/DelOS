/*
** DELOS PROJECT, 2025
** include/kernel/shell/shell
** File description:
** Shell header file
*/

#include "kernel/shell/parser/arguments.h"
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
    uint8_t (*func)(uint32_t argc, char *argv[]);
} shell_command_t;

/**
 * @brief All shell commands.
 */
extern const shell_command_t shell_commands[];

/**
 * @brief Execute the command
 *
 * @param argc               The ARGC
 * @param char *argv[16]     The ARGV
 *
 * @return The final exit code of the operation.
 */
uint8_t
kshell_execute_command(uint32_t argc, char *argv[SHELL_ARGV_MAX_COUNT]);

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
kshell_reboot(UNUSED uint32_t argc, UNUSED char *argv[]);

/**
 * @brief Command for help.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_help(UNUSED uint32_t argc, UNUSED char *argv[]);

/**
 * @brief Command for clear.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_clear(UNUSED uint32_t argc, UNUSED char *argv[]);

/**
 * @brief Command for uptime.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_uptime(UNUSED uint32_t argc, UNUSED char *argv[]);

#endif /* ifndef KERNEL_SHELL_H_ */
