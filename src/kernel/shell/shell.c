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
 *
 * @return OK_TRUE if worked KO_FALSE otherwise.
 */
bool32_t
kshell_start(void)
{
    uint8_t character = kkeyboard_getchar();

    ktty_putc((uint8_t) character, VGA_TEXT_DEFAULT_COLOR);
    return OK_TRUE;
}
