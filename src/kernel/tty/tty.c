/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY source file
*/

#include <utils/kstdlib/kstring.h>
#include <drivers/video/vga.h>
#include <kernel/tty/tty.h>
#include <defines.h>

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
ktty_putc_at(uint8_t x, uint8_t y, char c, uint8_t color)
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
ktty_putc(char c, uint8_t color)
{
    switch (c) {
        case '\b':
            if (ktty_cursor_pos._x > 0) {
                ktty_cursor_add(-1, 0);
            } else if (ktty_cursor_pos._y > 0) {
                ktty_cursor_set(VGA_COLUMNS_MAX - 1, ktty_cursor_pos._y - 1);
            }
            kvga_putc_at(ktty_cursor_pos._x, ktty_cursor_pos._y, ' ', VGA_TEXT_DEFAULT_COLOR);
            return;
            
        case '\n':
            if (ktty_cursor_pos._y >= VGA_LINES_MAX - 1) {
                kvga_scroll_line();
                ktty_cursor_set(0, VGA_LINES_MAX - 1);
            } else {
                ktty_cursor_set(0, ktty_cursor_pos._y + 1);
            }
            return; 

        default:
            ktty_putc_at(ktty_cursor_pos._x, ktty_cursor_pos._y, c, color);
            ktty_cursor_add(1, 0);
            return;
    }
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
ktty_puts_at(uint8_t x, uint8_t y, const char *const string, uint8_t color)
{
    uint8_t current_x = x;
    uint8_t current_y = y;

    if (string == NULL) {
        return;
    }
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
ktty_puts(const char *const string, uint8_t color)
{
    if (string == NULL) {
        return;
    }
    for (int i = 0; *(string + i); i++) {
        ktty_putc(*(string + i), color);
    }
}

/**
 * @brief Fill the TTY screen of c characters and colors.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_fill(char c, uint8_t color)
{
    kvga_fill(c, color);
}
