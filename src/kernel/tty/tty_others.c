/*
** DELOS PROJECT, 2025
** src/kernel/tty/tty_others
** File description:
** TTY others like numbers, decimals, hexadecimals source file
*/

#include <utils/kstdlib/kstring.h>
#include <drivers/video/vga.h>
#include <kernel/tty/tty.h>

/**
 * @brief Print a number on the screen at the TTY cursor position.
 *        This function use VGA text mode by default.
 *
 * @param c             The character
 * @param color         The color
 */
void
ktty_put_number(int32_t number, uint8_t color)
{
    uint32_t divisor = 1;
    int32_t divisor_temp = 0;

    if (number < 0) {
        ktty_putc('-', color);
        number = -number;
    }
    divisor_temp = number;
    while (divisor_temp >= 10) {
        divisor_temp /= 10;
        divisor *= 10;
    }
    while (divisor > 0) {
        ktty_putc(((number / divisor) % 10) + '0', color);
        divisor /= 10;
    }
}
