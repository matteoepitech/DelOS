/*
** DELOS PROJECT, 2025
** include/utils/kstdio
** File description:
** Kstdio header file
*/

#include <types.h>

#ifndef UTILS_KSTDLIB_KSTDIO_H_
    #define UTILS_KSTDLIB_KSTDIO_H_

/**
 * @brief Print formatted output to the screen using TTY API.
 *
 * This function provides a printf-like interface for kernel output with support
 * for various format specifiers and padding options.
 *
 * Format specifiers:
 *   %d  - Signed decimal integer (int32_t)
 *         Example: kprintf("%d", -42) → "-42"
 *
 *   %x  - Unsigned hexadecimal integer, lowercase (uint32_t)
 *         Example: kprintf("%x", 255) → "ff"
 *
 *   %X  - Unsigned hexadecimal integer, uppercase (uint32_t)
 *         Example: kprintf("%X", 255) → "FF"
 *
 *   %b  - Unsigned binary integer (uint32_t)
 *         Example: kprintf("%b", 5) → "101"
 *
 *   %p  - Pointer address (prefixed with "0x")
 *         Example: kprintf("%p", ptr) → "0x7fff1234"
 *
 *   %s  - Null-terminated string (char*)
 *         Example: kprintf("%s", "hello") → "hello"
 *         Note: NULL pointers are displayed as "(null)"
 *
 *   %c  - Single character (char)
 *         Example: kprintf("%c", 'A') → "A"
 *
 *   %%  - Literal percent sign
 *         Example: kprintf("100%%") → "100%"
 *
 * Padding options:
 *   %Nd   - Minimum width of N characters, padded with spaces on the left
 *           Example: kprintf("%5d", 42) → "   42"
 *
 *   %0Nd  - Minimum width of N characters, padded with zeros on the left
 *           Example: kprintf("%05d", 42) → "00042"
 *           Note: For negative numbers, sign is placed before zeros
 *           Example: kprintf("%05d", -42) → "-0042"
 *
 * Padding works with all numeric specifiers (%d, %x, %X, %b, %p) and strings.
 * Character specifiers (%c) use space padding only.
 *
 * @param color      The VGA text color to use for output
 * @param format     The format string buffer containing text and format specifiers
 * @param ...        The variadic arguments corresponding to format specifiers
 *
 * @return The total number of characters printed to the screen.
 */
uint32_t
kprintf(uint8_t color, char *format, ...);

#endif /* ifndef UTILS_KSTDLIB_KSTDIO_H_ */
