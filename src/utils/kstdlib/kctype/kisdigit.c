/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/ctype/kisdigit
** File description:
** kisdigit source file
*/

#include <utils/kstdlib/kctype.h>

/**
 * @brief Check if a specific character is a digit (0 <= digit >= 9).
 *
 * @param c  The character to check
 *
 * @return OK_TRUE if it's digit KO_FALSE otherwise.
 */
bool32_t
kisdigit(char c)
{
    return c >= '0' && c <= '9';
}
