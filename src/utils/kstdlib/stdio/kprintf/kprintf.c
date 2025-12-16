/*
** DELOS PROJECT, 2025
** src/utils/kstdlib/stdio/kprintf
** File description:
** Kprintf source file
*/

#include "utils/kstdlib/kstdarg.h"
#include "utils/kstdlib/kstdio.h"
#include "kernel/tty/tty.h"
#include "types.h"

/**
 * @brief Print in a format like printf on screen using TTY api.
 *
 * @param format     The format string buffer
 * @param ...        The variadic values
 *
 * @return The number of characters printed.
 */
uint32_t
kprintf(char *format, ...)
{
    kva_list va = KVA_START(format);

    return 0;
}
