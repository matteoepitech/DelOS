/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/timer
** File description:
** timer command source file
*/

#include "kernel/arch/i386/interruption/pit.h"
#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
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
    KPRINTF_INFO("Timer informations:");
    KPRINTF_INFO("  - Ticks count = %d", ticks_count);
    KPRINTF_INFO("  - Seconds count = %d", seconds_count);
    return KO_FALSE;
}
