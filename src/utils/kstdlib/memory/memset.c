/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/memory/memset
** File description:
** memset source file
*/

#include "utils/kstdlib/kmemory.h"

/**
 * @brief Kernel memset.
 *        Put the byte value at the addr for len bytes.
 *
 * @param addr          The address to start the set
 * @param byte          The byte to set
 * @param len           The n times we do it
 *
 * @return addr
 */
void *
kmemset(void *addr, uint8_t byte, size_t len)
{
    // TODO: add 4 bytes aligned memset
    uint8_t *ptr = (uint8_t *) addr;

    while (len) {
        *ptr = byte;
        ptr++;
        len--;
    }
    return addr;
}
