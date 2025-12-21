/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/pmm_dump
** File description:
** pmm_dump command source file
*/

#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for pmm_dump.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_pmm_dump(UNUSED uint32_t argc, UNUSED char *argv[])
{
    kpmm_dump();
    return KO_FALSE;
}
