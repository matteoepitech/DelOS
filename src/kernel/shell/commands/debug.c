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

uint8_t
kshell_debug(UNUSED uint32_t argc, UNUSED char *argv[])
{
    uint32_t va = 0xC0300000;
    uint32_t pd_index = VMM_GET_PDE_INDEX(va);
    uint32_t pt_index = VMM_GET_PTE_INDEX(va);
    uint32_t *pt = (uint32_t *) (0xFFC00000 + (pd_index << 12));
    page_table_entry_t pte = *(page_table_entry_t *)&pt[pt_index];

    KPRINTF_DEBUG("PTE for %x = %x (present=%d, frame=%x)\n", va, pte, pte._present, pte._frame);
    return OK_TRUE;
}
