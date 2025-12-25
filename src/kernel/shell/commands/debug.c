/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/vmm/vmm.h>
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
    vaddr_t vaddr = 0xC0100000;
    paddr_t paddr = 0x00100000;

    kvmm_map_page(vaddr, paddr, 0);
    return KO_FALSE;
}
