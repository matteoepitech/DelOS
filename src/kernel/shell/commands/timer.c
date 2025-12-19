/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/timer
** File description:
** timer command source file
*/

#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for timer.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_timer(UNUSED uint32_t argc, UNUSED char *argv[])
{
    uint32_t res_ms_int  = 1000 / PIT_TARGET_FREQUENCY;
    uint32_t res_ms_frac = (1000 % PIT_TARGET_FREQUENCY) * 100 / PIT_TARGET_FREQUENCY;

    KPRINTF_INFO("timer: PIT @ %dHz (%d.%02dms resolution)", PIT_TARGET_FREQUENCY, res_ms_int, res_ms_frac);
    return KO_FALSE;
}
