/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/memory/memmove
** File description:
** memmove source file
*/

#include "utils/kstdlib/kmemory.h"

/**
 * @brief Kernel memmove.
 *        Including backward memory move.
 *
 * @param dst           The address to start the move
 * @param src           The address where to take data from
 * @param n             The n times we do it
 *
 * @return dst
 */
void *
kmemmove(void *dst, const void *src, size_t n)
{
    const uint8_t *s = src;
    uint8_t *d = dst;
    void *ret = dst;

    if (s < d) {
        d += n - 1;
        s += n - 1;
        while (n) {
            *d-- = *s--;
            n--;
        }
    } else {
        while (n) {
            *d++ = *s++;
            n--;
        }
    }
    return ret;
}
