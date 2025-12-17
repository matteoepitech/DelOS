/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/shutdown
** File description:
** shutdown command source file
*/

#include "kernel/shell/shell.h"
#include "kernel/misc/panic.h"
#include "utils/misc/print.h"
#include "defines.h"

/**
 * @brief Command for shutdown.
 *        WARN: This command is only working for QEMU emulating mode.
 *        This is a I/O port for QEMU only for version > 2.0
 *
 *        For QEMU < 2.0 use this:
 *        outw(0xB004, 0x2000);
 *
 *        In virtual box use this:
 *        outw(0x4004, 0x3400);
 *
 *        In cloud hypervisor use this:
 *        outw(0x600, 0x34);
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_shutdown(UNUSED uint32_t argc, UNUSED char *argv[])
{    
    outw(0x604, 0x2000);
    KPANIC("Shutdown goes wrong.");
    return KO_FALSE;
}
