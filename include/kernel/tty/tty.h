/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty
** File description:
** TTY Header file
*/

#ifndef KERNEL_TTY_H_
    #define KERNEL_TTY_H_

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
tty_putc_at(unsigned char x, unsigned char y, unsigned char c, unsigned char color);

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
tty_puts_at(unsigned char x, unsigned char y, const char *string, unsigned char color);

#endif /* ifndef KERNEL_TTY_H_ */
