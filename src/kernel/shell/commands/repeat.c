/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/repeat
** File description:
** repeat command source file
*/

#include "utils/kstdlib/kstdlib.h"
#include "kernel/shell/shell.h"
#include "utils/misc/print.h"
#include "defines.h"

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

    if (argc < 3) {
        KPRINTF_ERROR("usage: repeat <n> <cmd> <args>...");
        return OK_TRUE;
    }
    repeat_times = katoi(argv[1]);
    if (repeat_times <= 0) {
        KPRINTF_ERROR("repeat: the n value must be greater than 0");
        return OK_TRUE;
    }
    for (; repeat_times > 0; repeat_times--) {
        kshell_execute_command(argc - 2, &argv[2]);
    }
    return KO_FALSE;
}
