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
    paddr_t pd_frame = (paddr_t) kpmm_alloc_pages(1);

    *((uint32_t *) (0xC0400000)) = 32;
    return 0;
    KPRINTF_DEBUG("%x", pd_frame);
    if (kvmm_map_page(0xC0400000, pd_frame, VMM_FLAG_USER | VMM_FLAG_RW | VMM_FLAG_PRESENT)) {
        KPRINTF_DEBUG("Vaddr %x, is mapped to Paddr %x.", 0xC0400000, pd_frame);
        kvmm_unmap_page(0xC0400000);
        kpmm_free_pages((void *) pd_frame, 1);
        KPRINTF_DEBUG("Vaddr %x, is unmapped.", 0xC0400000);
    }
    return OK_TRUE;
}
