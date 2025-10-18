/*
** DELOS PROJECT, 2025
** include/kernel/misc/panic
** File description:
** Panic header file
*/

#ifndef KERNEL_MISC_PANIC_H_
    #define KERNEL_MISC_PANIC_H_

#ifndef KPANIC
    #define KPANIC(msg) kpanic(msg)
#endif /* ifndef KPANIC
 */

/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg           The optionnal message (can be NULL)
 */
void
kpanic(const char *msg);

#endif /* ifndef KERNEL_MISC_PANIC_H_ */
