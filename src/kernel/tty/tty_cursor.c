/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty_cursor
** File description:
** TTY cursor source file
*/

#include "drivers/video/vga.h"
#include "kernel/tty/tty.h"

/**
 * @brief Variable tty_cursor_pos contain a structure for representing the
 *        TTY cursor position in a VGA mode.
 *        It use a 8 bits (1 byte) point structure since text mode used is
 *        limited to a 80x25 screen coordinates.
 */
point8_t ktty_cursor_pos = {0, 0};

/**
 * @brief Get a copy of the TTY cursor position in a structure of char values.
 *
 * @return The point8_t structure.
 */
point8_t
ktty_cursor_get_copy(void)
{
    return ktty_cursor_pos;
}

/**
 * @brief Get a ptr of the TTY cursor position in a structure of char values.
 *
 * @return The point8_t structure.
 */
point8_t *
ktty_cursor_get_ptr(void)
{
    return &ktty_cursor_pos;
}

/**
 * @brief Set the cursor position to a X and Y values.
 *
 * @param x             The X coordinate
 * @param y             The Y coordinate
 */
void
ktty_cursor_set(unsigned char x, unsigned char y)
{
    ktty_cursor_pos._x = x;
    ktty_cursor_pos._y = y;
}

/**
 * @brief Move the TTY cursor by these value.
 *        If x > VGA_COLUMNS_MAX then it will transform it into a line.
 *
 * @param x             The amount of columns to add
 * @param y             The amount of lines to add
 */
void
ktty_cursor_add(int32_t x, int32_t y)
{
    int32_t real_x = ((int32_t) ktty_cursor_pos._x) + x;
    int32_t real_y = ((int32_t) ktty_cursor_pos._y) + y;

    if (real_x >= VGA_COLUMNS_MAX) {
        real_y += real_x / VGA_COLUMNS_MAX;
        real_x = real_x % VGA_COLUMNS_MAX;
    }
    // TODO: if y > VGA_LINES_MAX, move the vga memory buffer by VGA_COLUMNS_MAX on top and erasing top data
    ktty_cursor_set(real_x, real_y);
}
