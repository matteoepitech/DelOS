/*
** DELOS PROJECT, 2025
** src/utils/misc/bitops
** File description:
** Bit operation source file
*/

#include <utils/misc/bitops.h>

/**
 * @brief Check if there is a free bit in a byte.
 *
 * @param byte   The byte to check
 *
 * @return The index if worked, -1 if no free.
 */
int32_t
kbyte_has_free_bit(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++) {
        if ((byte & (1 << i)) == 0) {
            return i;
        }
    }
    return -1;
}
