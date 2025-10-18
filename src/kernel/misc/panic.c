/*
** DELOS PROJECT, 2025
** src/kernel/misc/panic
** File description:
** Panic source file
*/

#include "kernel/interruption/interruption.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Print a kernel panic message and stop the kernel by infinite loop.
 *
 * @param msg           The optionnal message (can be NULL)
 */
void
kpanic(const char *msg)
{
    if (msg == NULL) {
        KERROR_TTY("KERNEL PANIC!");
    } else {
        KERROR_TTY("KERNEL PANIC!");
        KDEBUG_TTY(" > ");
        KDEBUG_TTY(msg);
    }
    kstop_interruption();
    while (1);
}
