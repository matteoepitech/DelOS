/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/timer
** File description:
** timer command source file
*/

#include "kernel/interruption/pit.h"
#include "kernel/shell/shell.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Command for timer.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_timer(UNUSED int argc, UNUSED char *argv[])
{
    KDEBUG_TTY("Timer informations:\n");
    KDEBUG_TTY("  - Ticks count = ");
    KDEBUG_TTY_NUMBER(ticks_count);
    KDEBUG_TTY("\n");
    KDEBUG_TTY("  - Seconds count = ");
    KDEBUG_TTY_NUMBER(seconds_count);
    KDEBUG_TTY("\n");
    return KO_FALSE;
}
