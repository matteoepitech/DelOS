/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/string/strcmp
** File description:
** strcmp source file
*/

#include "utils/kstdlib/kstring.h"

/**
 * @brief Get the difference between the first non equal character.
 *
 * @param string_a      The string A
 * @param string_b      The string B
 *
 * @return The difference between the first non equal character.
 */
int32_t
kstrcmp(const char *string_a, const char *string_b)
{
    while (*string_a == *string_b && *string_a) {
        string_a++;
        string_b++;
    }
    return *string_a - *string_b;
}
