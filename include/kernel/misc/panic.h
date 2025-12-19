/*
** DELOS PROJECT, 2025
** include/kernel/misc/panic
** File description:
** Panic header file
*/

#include <types.h>

#ifndef KERNEL_MISC_PANIC_H_
    #define KERNEL_MISC_PANIC_H_

    #ifndef KPANIC
        #define KPANIC(msg) kpanic(msg, __FILE__, __LINE__)
    #endif /* ifndef KPANIC */

/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg    The optionnal message (can be NULL)
 * @param file   The file where the panic come from
 * @param line   The line where the panic come from
 */
void
kpanic(const char *msg, const char *file, uint32_t line);

#endif /* ifndef KERNEL_MISC_PANIC_H_ */
