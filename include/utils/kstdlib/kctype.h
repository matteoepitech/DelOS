/*
** DELOS PROJECT, 2025
** include/utils/kctype
** File description:
** Kctype header file
*/

#include <types.h>

#ifndef UTILS_KSTDLIB_KCTYPE_H_
    #define UTILS_KSTDLIB_KCTYPE_H_

/**
 * @brief Check if a specific character is a digit (0 <= digit >= 9).
 *
 * @param c  The character to check
 *
 * @return OK_TRUE if it's digit KO_FALSE otherwise.
 */
bool32_t
kisdigit(char c);

/**
 * @brief Say if a character (byte or more) is actually printable.
 *
 * @param character  The character to check if printable
 *
 * @return OK_TRUE if printable, KO_FALSE otherwise.
 */
bool32_t
kisprint(int32_t character);

#endif /* ifndef UTILS_KSTDLIB_KCTYPE_H_ */
