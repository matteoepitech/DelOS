/*
** DELOS PROJECT, 2025
** src/utils/string/kstrcpy
** File description:
** kstrcpy source file
*/

#include <utils/kstdlib/kstring.h>
#include <defines.h>

/**
 * @brief Copy a literal string into a pointer.
 *
 * @param dst        Where to copy
 * @param src        The string to copy
 *
 * @return The pointer to the destination.
 */
char *
kstrcpy(char *dst, const char *src)
{
    char *res = dst;

    if (dst == NULL || src == NULL) {
        return dst;
    }
    while (*src) {
        *dst = *src;
        dst++;
        src++;
    }
    return res;
}
