/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/memory/memcpy
** File description:
** memcpy source file
*/

#include "utils/kstdlib/kmemory.h"

/**
 * @brief Kernel memcpy.
 *
 * @param dst           The address to start the copy
 * @param src           The address where to take data from
 * @param n             The n times we do it
 *
 * @return dst
 */
void *
kmemcpy(void *restrict dst, const void *restrict src, size_t n)
{
    void *ret = dst;

    while (n) {
        *(uint8_t *) dst = *(uint8_t *) src;
        dst++;
        src++;
        n--;
    }
    return ret;
}
