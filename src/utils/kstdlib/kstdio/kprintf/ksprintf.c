/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdio/ksprintf
** File description:
** Ksprint source file
*/

#include <utils/kstdlib/kstdarg.h>
#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/kstdio.h>
#include <defines.h>

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
 * @brief Divide a 64-bit unsigned value by a 32-bit base without libgcc helpers.
 *
 * @param value  The value to divide
 * @param base   The base (assumed > 1 and small: 2, 10, 16)
 * @param rem    Output: the remainder (can be NULL)
 *
 * @return The quotient.
 */
static uint64_t
kdivmod_u64(uint64_t value, uint32_t base, uint32_t *rem)
{
    uint64_t quotient = 0;
    uint64_t carry = 0;

    for (int i = 63; i >= 0; i--) {
        carry = (carry << 1) | ((value >> i) & 1ULL);
        if (carry >= base) {
            carry -= base;
            quotient |= 1ULL << i;
        }
    }
    if (rem != NULL) {
        *rem = (uint32_t) carry;
    }
    return quotient;
}

/**
 * @brief Convert an unsigned 64-bit integer to string in given base.
 *
 * @param value      The value to convert
 * @param base       The base (2, 10, 16)
 * @param buffer     The output buffer
 * @param uppercase  Use uppercase for hex (A-F)
 *
 * @return The length of the string.
 */
static uint32_t
kuitoa64(uint64_t value, uint32_t base, char *buffer, uint8_t uppercase)
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
        uint32_t remainder = 0;

        value = kdivmod_u64(value, base, &remainder);
        temp[i++] = digits[remainder];
    }
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
    return j;
}

/**
 * @brief Convert a signed 64-bit integer to string.
 *
 * @param value      The value to convert
 * @param buffer     The output buffer
 *
 * @return The length of the string.
 */
static uint32_t
kitoa64(int64_t value, char *buffer)
{
    uint32_t len = 0;

    if (buffer == NULL) {
        return 0;
    }
    if (value < 0) {
        buffer[0] = '-';
        len = 1 + kuitoa64((uint64_t) -value, 10, buffer + 1, KO_FALSE);
    } else {
        len = kuitoa64((uint64_t) value, 10, buffer, KO_FALSE);
    }
    return len;
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
 * @brief Write len bytes from src into out buffer pointer.
 *
 * @param out    Pointer to the output cursor
 * @param src    The source buffer
 * @param len    Amount of bytes to write
 */
static void
kbuf_write(char **out, const char *src, uint32_t len)
{
    if (out == NULL || *out == NULL || src == NULL) {
        return;
    }
    for (uint32_t i = 0; i < len; i++) {
        **out = src[i];
        (*out)++;
    }
}

/**
 * @brief Apply padding to a string and write it to the buffer.
 *
 * @param out        Pointer to the output cursor
 * @param str        The string to write
 * @param len        The length of the string
 * @param width      The minimum width
 * @param pad_char   The padding character ('0' or ' ')
 *
 * @return The number of characters written.
 */
static uint32_t
kprint_padded(char **out, char *str, uint32_t len, uint32_t width, char pad_char)
{
    uint32_t count = 0;
    uint32_t padding = 0;

    if (out == NULL || str == NULL) {
        return 0;
    }
    if (width > len) {
        padding = width - len;
    }
    if (str[0] == '-' && pad_char == '0' && padding > 0) {
        **out = '-';
        (*out)++;
        count++;
        str++;
        len--;
    }
    while (padding > 0) {
        **out = pad_char;
        (*out)++;
        count++;
        padding--;
    }
    kbuf_write(out, str, len);
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
 * @brief Handle format specifier and write corresponding value.
 *
 * @param out        Pointer to the output cursor
 * @param format     The format string
 * @param i          The current index (will be updated)
 * @param va         The variadic argument list
 *
 * @return The number of characters written.
 */
static uint32_t
khandle_format(char **out, char *format, uint32_t *i, kva_list *va)
{
    char buffer[64];
    uint32_t width = 0;
    uint8_t pad_zero = KO_FALSE;
    uint32_t len = 0;
    uint32_t value = 0;
    uint8_t is_long = KO_FALSE;
    char *str = NULL;
    char c = 0;
    char pad_char = ' ';

    if (out == NULL || format == NULL || i == NULL || va == NULL) {
        return 0;
    }
    kparse_format(format, i, &width, &pad_zero);
    if (pad_zero == OK_TRUE) {
        pad_char = '0';
    }
    if (format[*i] == 'l') {
        is_long = OK_TRUE;
        (*i)++;
    }
    switch (format[*i]) {
        case 'd':
            if (is_long == OK_TRUE) {
                int64_t value64 = KVA_ARG(*va, int64_t);

                len = kitoa64(value64, buffer);
                return kprint_padded(out, buffer, len, width, pad_char);
            }
            value = KVA_ARG(*va, int32_t);
            len = kitoa((int32_t) value, buffer);
            return kprint_padded(out, buffer, len, width, pad_char);
        case 'x':
            if (is_long == OK_TRUE) {
                uint64_t value64 = KVA_ARG(*va, uint64_t);

                kbuf_write(out, "0x", 2);
                len = kuitoa64(value64, 16, buffer, KO_FALSE);
                return 2 + kprint_padded(out, buffer, len, width, pad_char);
            }
            value = KVA_ARG(*va, uint32_t);
            kbuf_write(out, "0x", 2);
            len = kuitoa(value, 16, buffer, KO_FALSE);
            return 2 + kprint_padded(out, buffer, len, width, pad_char);
        case 'X':
            value = KVA_ARG(*va, uint32_t);
            kbuf_write(out, "0X", 2);
            len = kuitoa(value, 16, buffer, OK_TRUE);
            return 2 + kprint_padded(out, buffer, len, width, pad_char);
        case 'b':
            value = KVA_ARG(*va, uint32_t);
            len = kuitoa(value, 2, buffer, KO_FALSE);
            return kprint_padded(out, buffer, len, width, pad_char);
        case 'p':
            value = KVA_ARG(*va, uint32_t);
            kbuf_write(out, "0x", 2);
            len = kuitoa(value, 16, buffer, KO_FALSE);
            return 2 + kprint_padded(out, buffer, len, width > 2 ? width - 2 : 0, pad_char);
        case 's':
            str = KVA_ARG(*va, char *);
            if (str == NULL) {
                str = "(null)";
            }
            len = kstrlen(str);
            return kprint_padded(out, str, len, width, ' ');
        case 'c':
            c = (char) KVA_ARG(*va, int);
            buffer[0] = c;
            buffer[1] = '\0';
            return kprint_padded(out, buffer, 1, width, ' ');
        case '%':
            **out = '%';
            (*out)++;
            return 1;
        default:
            **out = '%';
            (*out)++;
            **out = format[*i];
            (*out)++;
            return 2;
    }
}

/**
 * @brief Write formatted output to a buffer (like sprintf).
 *
 * This function provides a printf-like interface but writes into the given
 * buffer instead of the TTY. The supported format specifiers and padding
 * options are identical to kprintf.
 *
 * @param buffer     The output buffer (must be large enough)
 * @param format     The format string buffer containing text and format specifiers
 * @param ...        The variadic arguments corresponding to format specifiers
 *
 * @return Number of characters written, excluding the terminating null byte.
 */
uint32_t
ksprintf(char *buffer, char *format, ...)
{
    kva_list va = KVA_START(format);
    uint32_t i = 0;
    uint32_t count = 0;
    char *out = buffer;

    if (buffer == NULL || format == NULL) {
        return 0;
    }
    while (format[i]) {
        if (format[i] == '%' && format[i + 1]) {
            i++;
            count += khandle_format(&out, format, &i, &va);
        } else {
            *out = format[i];
            out++;
            count++;
        }
        i++;
    }
    *out = '\0';
    return count;
}
