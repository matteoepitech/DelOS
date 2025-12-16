/*
** DELOS PROJECT, 2025
** include/utils/kstdio
** File description:
** Kstdio header file
*/

#include "types.h"

#ifndef UTILS_KSTDLIB_KSTDIO_H_
    #define UTILS_KSTDLIB_KSTDIO_H_

/**
 * @brief Print in a format like printf on screen using TTY api.
 *
 * @param format     The format string buffer
 * @param ...        The variadic values
 *
 * @return The number of characters printed.
 */
uint32_t
kprintf(char *format, ...);

#endif /* ifndef UTILS_KSTDLIB_KSTDIO_H_ */
