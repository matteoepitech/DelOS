/*
** EPITECH PROJECT, 2025
** src/utils/kstring
** File description:
** Kstring source file
*/

#include "utils/string.h"

/**
 * @brief Get the length of a string.
 *
 * @param string        The string
 *
 * @return The length of it until a zero terminated byte.
 */
uint32_t
kstrlen(const int8_t *const string)
{
    uint32_t len = 0;

    while (*(string + len)) {
        len++;
    }
    return len;
}
