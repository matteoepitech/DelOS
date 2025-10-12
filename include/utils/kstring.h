/*
** EPITECH PROJECT, 2025
** include/utils/kstring
** File description:
** Kstring header file
*/

#include <stdint.h>

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
kstrlen(const char *const string);

#endif /* ifndef UTILS_KSTRING_H_ */
