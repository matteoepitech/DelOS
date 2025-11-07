/*
** EPITECH PROJECT, 2025
** src/kernel/shell/shell
** File description:
** Shell source file
*/

#include "kernel/misc/keyboard.h"
#include "kernel/shell/shell.h"
#include "kernel/tty/tty.h"
#include "defines.h"

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

    while (OK_TRUE) {
        uint8_t c = kkeyboard_getchar();

        switch (c) {
            case '\n':
                buffer[index] = '\0';
                ktty_puts("\n", VGA_TEXT_DEFAULT_COLOR);
                index = 0;
                break;
            case '\b':
                if (index > 0) {
                    index--;
                    ktty_putc('\b', VGA_TEXT_DEFAULT_COLOR);
                    ktty_putc(' ', VGA_TEXT_DEFAULT_COLOR);
                    ktty_putc('\b', VGA_TEXT_DEFAULT_COLOR);
                }
                break;
            default:
                if (index < KERNEL_SHELL_BUFFER_SIZE - 1) {
                    buffer[index++] = c;
                    ktty_putc(c, VGA_TEXT_DEFAULT_COLOR);
                }
                break;
        }
    }
    return OK_TRUE;
}
