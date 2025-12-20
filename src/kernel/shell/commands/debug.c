/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

#include <utils/kstdlib/kstring.h>

/**
 * @brief Command for debug.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_debug(UNUSED uint32_t argc, UNUSED char *argv[])
{
    char *c_string = "Salut tout le monde";
    uint32_t c_string_length = kstrlen(c_string);
    char *string_dupped = kearly_malloc(c_string_length + 1);

    for (uint32_t i = 0; i < c_string_length + 1; i++) {
        string_dupped[i] = c_string[i];
    }
    KPRINTF_DEBUG("%p", string_dupped);
    return KO_FALSE;
}
