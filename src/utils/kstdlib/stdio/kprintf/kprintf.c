/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdio/kprintf
** File description:
** Kprintf source file
*/

#include "utils/kstdlib/kstdarg.h"
#include "utils/kstdlib/kstring.h"
#include "utils/kstdlib/kstdio.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Convert an unsigned integer to string in given base.
 *
 * @param value      The value to convert
 * @param base       The base (2, 10, 16)
 * @param buffer     The output buffer
 * @param uppercase  Use uppercase for hex (A-F)
 *
 * @return The length of the string.
 */
static uint32_t
kuitoa(uint32_t value, uint32_t base, char *buffer, uint8_t uppercase)
{
    char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char temp[32];
    uint32_t i = 0;
    uint32_t j = 0;

    if (buffer == NULL) {
        return 0;
    }
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }
    while (value > 0) {
        temp[i++] = digits[value % base];
        value /= base;
    }
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
    return j;
}

/**
 * @brief Convert a signed integer to string.
 *
 * @param value      The value to convert
 * @param buffer     The output buffer
 *
 * @return The length of the string.
 */
static uint32_t
kitoa(int32_t value, char *buffer)
{
    uint32_t len = 0;

    if (buffer == NULL) {
        return 0;
    }
    if (value < 0) {
        buffer[0] = '-';
        len = 1 + kuitoa((uint32_t) -value, 10, buffer + 1, KO_FALSE);
    } else {
        len = kuitoa((uint32_t) value, 10, buffer, KO_FALSE);
    }
    return len;
}

/**
 * @brief Apply padding to a string and print it.
 *
 * @param str        The string to print
 * @param len        The length of the string
 * @param width      The minimum width
 * @param pad_char   The padding character ('0' or ' ')
 * @param color      The color to use for output
 *
 * @return The number of characters printed.
 */
static uint32_t
kprint_padded(char *str, uint32_t len, uint32_t width, char pad_char, uint8_t color)
{
    uint32_t count = 0;
    uint32_t padding = 0;
    char pad[2] = {pad_char, '\0'};

    if (str == NULL) {
        return 0;
    }
    if (width > len) {
        padding = width - len;
    }
    if (str[0] == '-' && pad_char == '0' && padding > 0) {
        ktty_puts("-", color);
        count++;
        str++;
        len--;
    }
    while (padding > 0) {
        ktty_puts(pad, color);
        count++;
        padding--;
    }
    ktty_puts(str, color);
    count += len;
    return count;
}

/**
 * @brief Parse format width and flags.
 *
 * @param format     The format string
 * @param i          The current index (will be updated)
 * @param width      Output: the width value
 * @param pad_zero   Output: whether to pad with zeros
 */
static void
kparse_format(char *format, uint32_t *i, uint32_t *width, uint8_t *pad_zero)
{
    if (format == NULL || i == NULL || width == NULL || pad_zero == NULL) {
        return;
    }
    *width = 0;
    *pad_zero = KO_FALSE;
    if (format[*i] == '0') {
        *pad_zero = OK_TRUE;
        (*i)++;
    }
    while (format[*i] >= '0' && format[*i] <= '9') {
        *width = *width * 10 + (format[*i] - '0');
        (*i)++;
    }
}

/**
 * @brief Handle format specifier and print corresponding value.
 *
 * @param format     The format string
 * @param i          The current index (will be updated)
 * @param va         The variadic argument list
 * @param color      The color to use for output
 *
 * @return The number of characters printed.
 */
static uint32_t
khandle_format(char *format, uint32_t *i, kva_list *va, uint8_t color)
{
    char buffer[64];
    uint32_t width = 0;
    uint8_t pad_zero = KO_FALSE;
    uint32_t len = 0;
    uint32_t value = 0;
    char *str = NULL;
    char c = 0;
    char pad_char = ' ';

    if (format == NULL || i == NULL || va == NULL) {
        return 0;
    }
    kparse_format(format, i, &width, &pad_zero);
    if (pad_zero == OK_TRUE) {
        pad_char = '0';
    }
    switch (format[*i]) {
        case 'd':
            value = KVA_ARG(*va, int32_t);
            len = kitoa((int32_t)value, buffer);
            return kprint_padded(buffer, len, width, pad_char, color);
        case 'x':
            value = KVA_ARG(*va, uint32_t);
            len = kuitoa(value, 16, buffer, KO_FALSE);
            return kprint_padded(buffer, len, width, pad_char, color);
        case 'X':
            value = KVA_ARG(*va, uint32_t);
            len = kuitoa(value, 16, buffer, OK_TRUE);
            return kprint_padded(buffer, len, width, pad_char, color);
        case 'b':
            value = KVA_ARG(*va, uint32_t);
            len = kuitoa(value, 2, buffer, KO_FALSE);
            return kprint_padded(buffer, len, width, pad_char, color);
        case 'p':
            value = KVA_ARG(*va, uint32_t);
            ktty_puts("0x", color);
            len = kuitoa(value, 16, buffer, KO_FALSE);
            return 2 + kprint_padded(buffer, len, width > 2 ? width - 2 : 0, pad_char, color);
        case 's':
            str = KVA_ARG(*va, char *);
            if (str == NULL)
                str = "(null)";
            len = kstrlen(str);
            return kprint_padded(str, len, width, ' ', color);
        case 'c':
            c = (char)KVA_ARG(*va, int);
            buffer[0] = c;
            buffer[1] = '\0';
            return kprint_padded(buffer, 1, width, ' ', color);
        case '%':
            ktty_puts("%", color);
            return 1;
        default:
            ktty_puts("%", color);
            ktty_puts(&format[*i], color);
            return 2;
    }
}

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
kprintf(uint8_t color, char *format, ...)
{
    kva_list va = KVA_START(format);
    uint32_t i = 0;
    uint32_t count = 0;
    char c[2] = {0, 0};

    if (format == NULL) {
        return 0;
    }
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            count += khandle_format(format, &i, &va, color);
        } else {
            c[0] = format[i];
            ktty_puts(c, color);
            count++;
        }
        i++;
    }
    return count;
}
