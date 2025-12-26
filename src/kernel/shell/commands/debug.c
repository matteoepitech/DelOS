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
    uint32_t pd_index = va >> 22;           // 768
    uint32_t pt_index = (va >> 12) & 0x3FF; // 768
    uint32_t *pt = (uint32_t *)(0xFFC00000 + (pd_index * 4096));
    uint32_t pte = pt[pt_index];

    KPRINTF_DEBUG("PTE for 0x%x = 0x%x (present=%d, frame=0x%x)\n",
        va, pte, pte & 1, pte >> 12);
    return OK_TRUE;
}
