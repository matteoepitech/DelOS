/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/string/kstrcat
** File description:
** kstrcat source file
*/

#include <utils/kstdlib/kstring.h>
#include <defines.h>

/**
 * @brief Concat the string b into the string a.
 *        This function assumes that you have enough allocated memory for the dest.
 *
 * @param string_a   The destination 
 * @param string_b   The source
 *
 * @return The destination
 */
char *
kstrcat(char *restrict string_a, const char *restrict string_b)
{
    char *dest = string_a;

    if (string_a == NULL || string_b == NULL) {
        return NULL;
    }
    for (; *string_a; string_a++);
    while (*string_b) {
        *string_a = *string_b;
        string_a++;
        string_b++;
    }
    *string_a = '\0';
    return dest;
}
