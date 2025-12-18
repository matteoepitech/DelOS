/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/string/kstrcmp
** File description:
** kstrcmp source file
*/

#include "utils/kstdlib/kstring.h"
#include "defines.h"

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
    if (string_a == NULL || string_b == NULL) {
        return -1;
    }
    while (*string_a == *string_b && *string_a) {
        string_a++;
        string_b++;
    }
    return *string_a - *string_b;
}
