/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/pmm/pmm.h>
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
    char *string_mem = kpmm_alloc_pages(2); // 8192 bytes

    for (int i = 0; i < 8192; i++) {
        string_mem[i] = 'K';
    }
    KPRINTF_DEBUG("The string mem addr: %p", string_mem);
    return KO_FALSE;
}
