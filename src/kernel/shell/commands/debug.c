/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <defines.h>

uint8_t
kshell_debug(UNUSED uint32_t argc, UNUSED char *argv[])
{
    void *physical = kpmm_alloc_pages(1);
    KPRINTF_DEBUG("Physical allocated: 0x%x\n", physical);

    void *virtual = (void *) (0xC0400000);
    KPRINTF_DEBUG("Virtual target: 0x%x\n", virtual);

    KPRINTF_DEBUG("Before kvmm_map_page...\n");
    kvmm_map_page((uint32_t) virtual, (uint32_t) physical, 0);

    KPRINTF_DEBUG("After kvmm_map_page...\n");

    KPRINTF_DEBUG("Testing write...\n");
    *(uint32_t *)virtual = 0xDEADBEEF;

    KPRINTF_DEBUG("Testing read...\n");
    uint32_t value = *(uint32_t *)virtual;

    KPRINTF_DEBUG("Value read: 0x%x\n", value);
    return OK_TRUE;
}
