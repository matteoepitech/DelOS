/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_manager
** File description:
** VMM manager source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <utils/kstdlib/kmemory.h>
#include <defines.h>

/* @brief The page directory content of the major content of the OS */
__attribute__((aligned(4096))) page_directory_t kvmm_page_directory;

/* @brief The page directory content of the bootstrap kernel phase */
__attribute__((aligned(4096))) page_directory_t kvmm_boot_page_directory;

/* @brief The first page table content of the bootstrap kernel phase | NO need more IG ? */
__attribute__((aligned(4096))) page_table_t kvmm_boot_first_page_table;

/**
 * @brief Init the vmm manager with the page directory.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t kvmm_init(void)
{
    kmemset(&kvmm_page_directory, 0, sizeof(kvmm_page_directory));
    kmemset(&kvmm_boot_first_page_table, 0, sizeof(kvmm_boot_first_page_table));
    kmemset(&kvmm_boot_page_directory, 0, sizeof(kvmm_boot_page_directory));
    for (uint32_t i = 0; i < 1024; i++) {
        kvmm_boot_first_page_table._entries[i]._present = 1;
        kvmm_boot_first_page_table._entries[i]._rw = 1;
        kvmm_boot_first_page_table._entries[i]._frame = i;
    }
    kvmm_boot_page_directory._entries[0]._present = 1;
    kvmm_boot_page_directory._entries[0]._rw = 1;
    kvmm_boot_page_directory._entries[0]._table_addr = ((uint32_t) &kvmm_boot_first_page_table) >> 12;
    return OK_TRUE;
}
