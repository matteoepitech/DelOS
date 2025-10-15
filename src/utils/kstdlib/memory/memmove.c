/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/memory/memmove
** File description:
** memmove source file
*/

#include "utils/kstdlib/kmemory.h"

/**
 * @brief Kernel memmove.
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
    while (n) {
        *(uint8_t *) dst = *(uint8_t *) src;
        dst++;
        src++;
        n--;
    }
    return dst;
}
