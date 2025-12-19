/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdlib/kstrtol
** File description:
** kstrtol source file
*/

#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/klimits.h>
#include <utils/kstdlib/kctype.h>
#include <defines.h>

/**
 * @brief Skip every spaces.
 *
 * @param p  The pointer
 *
 * @return The new pointer.
 */
static const char *
skip_spaces(const char *p)
{
    for(; *p == ' ' || *p == '\t'; p++);
    return p;
}

/**
 * @brief The function to transform a character into is digit.
 *        '1' -> 1
 *        'A' -> 10
 *
 * @param c  The char to transform
 *
 * @return The transformed char into number, -1 if error.
 */
static int32_t
char_to_digit(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

/**
 * @brief Detect the base if the base parameter is 0.
 *
 * @param p      The pointer of the string
 * @param base   The base parameter
 *
 * @return The detected base in a integer.
 */
static int32_t
detect_base(const char **p, int32_t base)
{
    if (base != 0) {
        return base;
    }
    if ((*p)[0] == '0' && ((*p)[1] == 'x' || (*p)[1] == 'X')) {
        *p += 2;
        return 16;
    }
    if ((*p)[0] == '0') {
        (*p)++;
        return 8;
    }
    return 10;
}

/**
 * @brief Accumulate the result by a new digit and base.
 *
 * @param value  The current value
 * @param base   The base of the digit
 * @param digit  The digit to accumulate
 *
 * @return Accumulate the result.
 */
static int32_t
accumulate(int32_t *value, int32_t base, int32_t digit)
{
    if (*value > (K_LONG_MAX - digit) / base) {
        return 0;
    }
    *value = *value * base + digit;
    return 1;
}

/**
 * @brief Get the first number in a string.
 *
 * @param str    The string to parse
 * @param base   The base to parse the number, 0 if you don't know
 * @param ok     Put 1 in this addr space if worked, 0 otherwise
 *
 * @return The parsed number in a base.
 */
int32_t
kstrtol(const char *str, int32_t base, int32_t *ok)
{
    const char *p = NULL;
    int32_t value = 0;
    int32_t sign = 1;
    int32_t digit = 0;
    int32_t parsed = 0;

    if (ok != NULL) {
        *ok = 0;
    }
    if (str == NULL) {
        return 0;
    }
    p = skip_spaces(str);
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }
    base = detect_base(&p, base);
    if (base < 2 || base > 16) {
        return 0;
    }
    while (*p != '\0') {
        digit = char_to_digit(*p);
        if (digit < 0 || digit >= base)
            break;
        if (!accumulate(&value, base, digit))
            return 0;
        parsed = 1;
        p++;
    }
    if (parsed == 0) {
        return 0;
    }
    if (ok != NULL) {
        *ok = 1;
    }
    return value * sign;
}
