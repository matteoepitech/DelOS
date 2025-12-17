/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/reboot
** File description:
** Reboot command source file
*/

#include "kernel/misc/reboot.h"
#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
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
    KPRINTF_WARN("DelOS is trying to reboot...");
    kreboot();
    return KO_FALSE;
}
