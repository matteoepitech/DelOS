/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY Source file
*/

#include "kernel/tty/tty.h"
#include "drivers/video/vga.h"

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
    return vga_putc_at(x, y, c, color);
}

/**
 * @brief Print a character array on the screen at a certain coordinates.
 *        This function use VGA text mode by default.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
tty_puts_at(unsigned char x, unsigned char y, const char *string, unsigned char color)
{
}
