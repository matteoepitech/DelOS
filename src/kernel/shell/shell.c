/*
** EPITECH PROJECT, 2025
** src/kernel/shell/shell
** File description:
** Shell source file
*/

#include "utils/kstdlib/kstring.h"
#include "kernel/misc/keyboard.h"
#include "kernel/shell/shell.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief All shell commands.
 */
shell_command_t shell_commands[] = {
    {"help", kshell_help},
    {"reboot", kshell_reboot},
    {NULL, NULL}
};

/**
 * @brief Try to execute a command using the buffer.
 *
 * @param buffer                The buffer of the user prompt
 *
 * @return The final exit code of the operation.
 */
static uint8_t
try_execute_shell_command(char *buffer)
{
    for (uint32_t i = 0; shell_commands[i].command != NULL; i++) {
        if (kstrcmp(buffer, shell_commands[i].command) != 0)
            continue;
        shell_commands[i].func(1, &buffer);
    }
    return 1;
}

/**
 * @brief Start the shell and waiting for user prompt.
 *        This shell is the main process of the kernel and took the while.
 *
 * @return OK_TRUE if worked KO_FALSE otherwise.
 */
bool32_t
kshell_start(void)
{
    char buffer[KERNEL_SHELL_BUFFER_SIZE];
    uint32_t index = 0;

    ktty_puts("$> ", VGA_TEXT_PROMPT_COLOR);
    while (OK_TRUE) {
        uint8_t c = kkeyboard_getchar();

        switch (c) {
            case '\n':
                buffer[index] = '\0';
                ktty_puts("\n", VGA_TEXT_DEFAULT_COLOR);
                try_execute_shell_command(buffer);
                ktty_puts("$> ", VGA_TEXT_PROMPT_COLOR);
                index = 0;
                break;
            case '\b':
                if (index > 0) {
                    ktty_putc('\b', VGA_TEXT_DEFAULT_COLOR);
                    index--;
                }
                break;
            default:
                if (index < KERNEL_SHELL_BUFFER_SIZE - 1) {
                    buffer[index] = c;
                    ktty_putc(c, VGA_TEXT_DEFAULT_COLOR);
                    index++;
                }
                break;
        }
    }
    return OK_TRUE;
}
