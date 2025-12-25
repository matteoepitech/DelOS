/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_manager
** File description:
** VMM manager source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <utils/kstdlib/kmemory.h>
#include <defines.h>

/* @brief The page directory content */
page_directory_t kvmm_page_directory;

/**
 * @brief Init the vmm manager with the page directory.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_init(void)
{
    kwmemset(&kvmm_page_directory, 0, sizeof(kvmm_page_directory));
    return OK_TRUE;
}
