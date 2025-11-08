/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/reboot
** File description:
** Reboot command source file
*/

#include "kernel/misc/reboot.h"
#include "kernel/shell/shell.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Command for reboot.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_reboot(UNUSED int argc, UNUSED char *argv[])
{
    KDEBUG_TTY("Reboot time.\n");
    kreboot();
    return KO_FALSE;
}
