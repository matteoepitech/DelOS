/*
** DELOS PROJECT, 2025
** include/utils/kstdlib
** File description:
** Kstdlib header file
*/

#include <types.h>

#ifndef UTILS_KSTDLIB_KSTDLIB_H_
    #define UTILS_KSTDLIB_KSTDLIB_H_

/**
 * @brief Get an integer from a buffer.
 *        Value is max 2 147 483 647. (int32 max)
 *
 * @param buffer     The buffer to get the integer from
 *
 * @return The result on base 10 of the current buffer
 */
int32_t
katoi(const char *buffer);

/**
 * @brief Get the first number in a string.
 *
 * @param str    The string to parse
 * @param base   The base to parse the number, 0 if you don't know
 * @param ok     Put 1 in this addr space if worked, 0 otherwise
 *
 * @return The parsed number in a base.
 */
int64_t
kstrtol(const char *str, int32_t base, int32_t *ok);

#endif /* ifndef UTILS_KSTDLIB_KSTDLIB_H_ */
