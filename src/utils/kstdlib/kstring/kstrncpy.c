/*
** DELOS PROJECT, 2025
** src/utils/string/kstrncpy
** File description:
** kstrncpy source file
*/

#include <utils/kstdlib/kstring.h>
#include <defines.h>

/**
 * @brief Copy a literral string into a pointer.
 *
 * @param dst        Where to copy
 * @param src        The string to copy
 * @param n          The maximum of char to copy
 *
 * @return The pointer to the destination.
 */
char *
kstrncpy(char *dst, const char *src, size_t n)
{
    char *res = dst;

    if (dst == NULL || src == NULL || n == 0) {
        return dst;
    }
    while (*dst && n > 0) {
        *dst = *src;
        dst++;
        src++;
        n--;
    }
    return res;
}
