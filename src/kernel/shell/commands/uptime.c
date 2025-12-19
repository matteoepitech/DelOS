/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/uptime
** File description:
** uptime command source file
*/

#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>
#include <defines.h>

#ifndef UPTIME_SECONDS_PER_MINUTE
    #define UPTIME_SECONDS_PER_MINUTE 60
#endif /* ifndef UPTIME_SECONDS_PER_MINUTE */

/**
 * @brief Command for uptime.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_uptime(UNUSED uint32_t argc, UNUSED char *argv[])
{
    uint32_t seconds = seconds_count % UPTIME_SECONDS_PER_MINUTE;
    uint32_t ticks = ((ticks_count % PIT_TARGET_FREQUENCY) * 100) / PIT_TARGET_FREQUENCY;
    uint32_t minutes = seconds_count / UPTIME_SECONDS_PER_MINUTE;

    KPRINTF_INFO("uptime: %dm and %d.%02ds", minutes, seconds, ticks);
    return KO_FALSE;
}
