/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY source file
*/

#include "drivers/video/vga.h"
#include "kernel/tty/tty.h"
#include "utils/kstring.h"

/**
 * @brief Print a character on the screen at a certain coordinates.
 *        This function use VGA text mode by default.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
tty_putc_at(unsigned char x, unsigned char y, unsigned char c, unsigned char color)
{
    vga_putc_at(x, y, c, color);
}

/**
 * @brief Print a character array on the screen at a certain coordinates.
 *        This function use VGA text mode by default.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param string        The string
 * @param color         The color
 */
void
tty_puts_at(unsigned char x, unsigned char y, const char *const string, unsigned char color)
{
    for (int i = 0; *(string + i); i++) {
        vga_putc_at(x + i, y, *(string + i), color);
    }
}

/**
 * @brief Print a character array on the screen at the TTY cursor position.
 *
 * @param string        The character array
 * @param color         The color
 */
void
tty_puts(const char *const string, unsigned char color)
{
    tty_puts_at(tty_cursor_pos._x, tty_cursor_pos._y, string, color);
    tty_cursor_add(kstrlen(string), 0);
}
