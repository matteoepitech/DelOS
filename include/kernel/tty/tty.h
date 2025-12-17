/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY header file
*/

#include "drivers/video/vga.h"
#include "math/2d/point.h"

#ifndef KERNEL_TTY_H_
    #define KERNEL_TTY_H_

/**
 * @brief Variable tty_cursor_pos contain a structure for representing the
 *        TTY cursor position in a VGA mode.
 *        It use a 8 bits (1 byte) point structure since text mode used is
 *        limited to a 80x25 screen coordinates.
 *
 *        Declared in src/kernel/tty/tty_cursor.c
 */
extern point8_t ktty_cursor_pos;

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
ktty_putc_at(uint8_t x, uint8_t y, uint8_t c, uint8_t color);

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
ktty_puts_at(uint8_t x, uint8_t y, const char *const string, uint8_t color);

/**
 * @brief Print a character on the screen at the TTY cursor position.
 *        This function use VGA text mode by default.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_putc(uint8_t c, uint8_t color);

/**
 * @brief Print a character array on the screen at the TTY cursor position.
 *
 * @param string        The character array
 * @param color         The color
 */
void
ktty_puts(const int8_t *const string, uint8_t color);

/**
 * @brief Fill the TTY screen of c characters and colors.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_fill(uint8_t c, uint8_t color);

/**
 * @brief Get a copy of the TTY cursor position in a structure of char values.
 *
 * @return The point8_t structure.
 */
point8_t
ktty_cursor_get_copy(void);

/**
 * @brief Get a ptr of the TTY cursor position in a structure of char values.
 *
 * @return The point8_t structure.
 */
point8_t *
ktty_cursor_get_ptr(void);

/**
 * @brief Set the cursor position to a X and Y values.
 *
 * @param x             The X coordinate
 * @param y             The Y coordinate
 */
void
ktty_cursor_set(int8_t x, int8_t y);

/**
 * @brief Move the TTY cursor by these value.
 *        If x > VGA_COLUMNS_MAX then it will transform it into a line.
 *
 * @param x             The amount of columns to add
 * @param y             The amount of lines to add
 */
void
ktty_cursor_add(int32_t x, int32_t y);

/**
 * @brief Set the cursor visibility.
 *
 * @param visible       Visible or not
 */
void
ktty_cursor_set_visibility(bool32_t visible);

/**
 * @brief Print a number on the screen at the TTY cursor position.
 *        This function use VGA text mode by default.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_put_number(int32_t number, uint8_t color);

#endif /* ifndef KERNEL_TTY_H_ */
