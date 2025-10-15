/*
** EPITECH PROJECT, 2025
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
kstrlen(const int8_t *string);

#endif /* ifndef UTILS_KSTDLIB_KSTRING_H_ */
