/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/memory/memset
** File description:
** memset source file
*/

#include <utils/kstdlib/kmemory.h>
#include <defines.h>

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

    if (addr == NULL) {
        return NULL;
    }
    while (len) {
        *ptr = byte;
        ptr++;
        len--;
    }
    return addr;
}

/**
 * @brief Kernel word memset.
 *        Put the 2 bytes values at the addr for len bytes.
 *
 * @param addr          The address to start the set
 * @param word          The word to set
 * @param len           The n times we do it
 *
 * @return addr
 */
void *
kwmemset(void *addr, uint16_t word, size_t len)
{
    uint16_t *ptr = (uint16_t *) addr;

    if (addr == NULL) {
        return NULL;
    }
    while (len) {
        *ptr = word;
        ptr++;
        len--;
    }
    return addr;
}
