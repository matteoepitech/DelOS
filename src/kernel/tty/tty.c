/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY source file
*/

#include "drivers/video/vga.h"
#include "kernel/tty/tty.h"
#include "utils/string.h"

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
ktty_putc_at(unsigned char x, unsigned char y, unsigned char c, unsigned char color)
{
    kvga_putc_at(x, y, c, color);
}

/**
 * @brief Print a character on the screen at the TTY cursor position.
 *        This function use VGA text mode by default.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_putc(unsigned char c, unsigned char color)
{
    ktty_putc_at(ktty_cursor_pos._x, ktty_cursor_pos._y, c, color);
    ktty_cursor_add(1, 0);
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
ktty_puts_at(unsigned char x, unsigned char y, const char *const string, unsigned char color)
{
    unsigned char current_x = x;
    unsigned char current_y = y;

    for (int i = 0; *(string + i); i++) {
        ktty_putc_at(current_x, current_y, *(string + i), color);
        current_x++;
        if (current_x >= VGA_COLUMNS_MAX) {
            current_x = 0;
            current_y++;
        }
    }
}

/**
 * @brief Print a character array on the screen at the TTY cursor position.
 *
 * @param string        The character array
 * @param color         The color
 */
void
ktty_puts(const char *const string, unsigned char color)
{
    for (int i = 0; *(string + i); i++) {
        ktty_putc(*(string + i), color);
    }
}
