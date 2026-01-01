/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/system/panic_test
** File description:
** panic_test command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for panic_test.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_panic_test(UNUSED uint32_t argc, UNUSED char *argv[])
{
    KPANIC("This is a panic test.");
    return KO_FALSE;
}
