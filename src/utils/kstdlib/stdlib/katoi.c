/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdlib/katoi
** File description:
** katoi source file
*/

#include "utils/kstdlib/kstring.h"

/**
 * @brief Get an integer from a buffer.
 *
 * @param buffer     The buffer to get the integer from
 *
 * @return The result on base 10 of the current buffer
 */
int32_t
katoi(const char *buffer)
{
    int32_t result = 0;

    for (; *buffer; buffer++) {
        result = (result * 10) + (*buffer - '0');
    }
    return result;
}
