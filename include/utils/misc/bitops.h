/*
** DELOS PROJECT, 2025
** include/utils/misc/bitops
** File description:
** Bit operations header file
*/

#include <types.h>

#ifndef UTILS_MISC_BITOPS_H_
    #define UTILS_MISC_BITOPS_H_

/**
 * @brief Check if there is a free bit in a byte.
 *
 * @param byte   The byte to check
 *
 * @return The index if worked, -1 if no free.
 */
int32_t
kbyte_has_free_bit(uint8_t byte);

#endif /* ifndef UTILS_MISC_BITOPS_H_ */
