/*
** EPITECH PROJECT, 2025
** include/utils/kstring
** File description:
** Kstring header file
*/

#include "types.h"

#ifndef UTILS_KSTRING_H_
    #define UTILS_KSTRING_H_

/**
 * @brief Get the length of a string.
 *
 * @param string        The string
 *
 * @return The length of it until a zero terminated byte.
 */
uint32_t
kstrlen(const int8_t *const string);

#endif /* ifndef UTILS_KSTRING_H_ */
