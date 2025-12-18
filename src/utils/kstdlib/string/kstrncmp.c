/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/string/kstrncmp
** File description:
** kstrncmp source file
*/

#include "utils/kstdlib/kstring.h"
#include "defines.h"

/**
 * @brief Get the difference between the first non equal character.
 *
 * @param string_a      The string A
 * @param string_b      The string B
 * @param n             The number max of characters to check
 *
 * @return The difference between the first non equal character.
 */
int32_t
kstrncmp(const char *string_a, const char *string_b, uint32_t n)
{
    if (string_a == NULL || string_b == NULL) {
        return -1;
    }
    if (n == 0) {
        return n;
    }
    while (*string_a == *string_b && *string_a && n > 1) {
        string_a++;
        string_b++;
        n--;
    }
    return *string_a - *string_b;
}
