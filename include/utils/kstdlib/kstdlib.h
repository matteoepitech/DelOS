/*
** DELOS PROJECT, 2025
** include/utils/kstdlib
** File description:
** Kstdlib header file
*/

#include "types.h"

#ifndef UTILS_KSTDLIB_KSTDLIB_H_
    #define UTILS_KSTDLIB_KSTDLIB_H_

/**
 * @brief Get an integer from a buffer.
 *
 * @param buffer     The buffer to get the integer from
 *
 * @return The result on base 10 of the current buffer
 */
int32_t
katoi(const char *buffer);

#endif /* ifndef UTILS_KSTDLIB_KSTDLIB_H_ */
