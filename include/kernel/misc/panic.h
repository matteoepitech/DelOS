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

    /* @brief Do not use this KPANIC after the paging activated */
    #ifndef KPANIC_PHYS
        #define KPANIC_PHYS(msg) kpanic_phys(msg, __FILE__, __LINE__)
    #endif /* ifndef KPANIC_PHYS */

/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg    The optionnal message (can be NULL)
 * @param file   The file where the panic come from
 * @param line   The line where the panic come from
 */
void
kpanic(const char *msg, const char *file, uint32_t line);

/**
 * @brief Print a kernel panic message using physical VGA address and stop the kernel by infinite loop.
 *
 * @param msg    The optionnal message (can be NULL)
 * @param file   The file where the panic come from
 * @param line   The line where the panic come from
 */
void
kpanic_phys(const char *msg, const char *file, uint32_t line);

/**
 * @brief Display the current EIP value on the screen.
 */
void
kpanic_show_eip(void);

#endif /* ifndef KERNEL_MISC_PANIC_H_ */
