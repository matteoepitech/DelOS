/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/repeat
** File description:
** repeat command source file
*/

#include "utils/kstdlib/kstdlib.h"
#include "utils/kstdlib/kstring.h"
#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
#include "defines.h"

#ifndef REPEAT_HELP_MSG
    #define REPEAT_HELP_MSG "usage: repeat [-d | --details] <n> <cmd> <args>..."
#endif /* ifndef REPEAT_HELP_MSG */

/**
 * @brief Command for repeat.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_repeat(uint32_t argc, char *argv[])
{
    int32_t repeat_times = 0;
    uint8_t details = KO_FALSE;
    uint32_t start_ticks = 0;
    uint32_t cmd_argc = 0;
    char **cmd_argv = NULL;

    if (argc < 3) {
        KPRINTF_ERROR(REPEAT_HELP_MSG);
        return OK_TRUE;
    }
    if (kstrcmp(argv[1], "-d") == 0 || kstrcmp(argv[1], "--details") == 0) {
        details = OK_TRUE;
        if (argc < 4) {
            KPRINTF_ERROR(REPEAT_HELP_MSG);
            return OK_TRUE;
        }
        repeat_times = katoi(argv[2]);
        cmd_argc = argc - 3;
        cmd_argv = &argv[3];
    } else {
        repeat_times = katoi(argv[1]);
        cmd_argc = argc - 2;
        cmd_argv = &argv[2];
    }
    if (repeat_times <= 0) {
        KPRINTF_ERROR("repeat: the n value must be greater than 0");
        return OK_TRUE;
    }
    if (details == OK_TRUE) {
        start_ticks = ticks_count;
    }
    for (; repeat_times > 0; repeat_times--) {
        kshell_execute_command(cmd_argc, cmd_argv);
    }
    if (details == OK_TRUE) {
        KPRINTF_INFO("repeat: completed in %d ticks (%d.%03d seconds)",
            ticks_count - start_ticks, (ticks_count - start_ticks) / PIT_TARGET_FREQUENCY,
            (((ticks_count - start_ticks) % PIT_TARGET_FREQUENCY) * 1000) / PIT_TARGET_FREQUENCY
        );
    }

    return KO_FALSE;
}
