/*
** DELOS PROJECT, 2025
** src/utils/string/kstrlen
** File description:
** kstrlen source file
*/

#include "utils/kstdlib/kstring.h"

/**
 * @brief Get the length of a string.
 *
 * @param string        The string
 *
 * @return The length of it until a zero terminated byte.
 */
size_t
kstrlen(const char *string)
{
    size_t len = 0;

    while (*string) {
        string++;
        len++;
    }
    return len;
}
