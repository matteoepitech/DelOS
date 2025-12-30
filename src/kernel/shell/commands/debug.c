/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

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
    int *array = kmalloc(sizeof(int) * 1500);

    for (uint32_t i = 0; i < 1500; i++) {
        array[i] = 6;
    }

    kfree(array);
    return OK_TRUE;
}
