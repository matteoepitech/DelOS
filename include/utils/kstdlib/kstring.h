/*
** DELOS PROJECT, 2025
** include/utils/kstring
** File description:
** Kstring header file
*/

#include "types.h"

#ifndef UTILS_KSTDLIB_KSTRING_H_
    #define UTILS_KSTDLIB_KSTRING_H_

/**
 * @brief Get the length of a string.
 *
 * @param string        The string
 *
 * @return The length of it until a zero terminated byte.
 */
size_t
kstrlen(const char *string);

/**
 * @brief Get the difference between the first non equal character.
 *
 * @param string_a      The string A
 * @param string_b      The string B
 *
 * @return The difference between the first non equal character.
 */
int32_t
kstrcmp(const char *string_a, const char *string_b);

#endif /* ifndef UTILS_KSTDLIB_KSTRING_H_ */
