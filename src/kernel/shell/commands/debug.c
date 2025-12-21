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
    uint32_t bit = kpmm_bitmap_get_next();
    kpmm_bitmap_set_value(bit, OK_TRUE);
    uint32_t bit_2 = kpmm_bitmap_get_next();
    kpmm_bitmap_set_value(bit_2, OK_TRUE);

    KPRINTF_DEBUG("First: %d\nSecond: %d", bit, bit_2);
    return KO_FALSE;
}
