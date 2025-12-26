/*
** DELOS PROJECT, 2025
** src/kernel/memory/vmm/vmm_manager
** File description:
** VMM manager source file
*/

#include <kernel/memory/vmm/vmm.h>
#include <utils/kstdlib/kmemory.h>
#include <kernel/memory/mmu.h>
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
    uint32_t page_table_phys = (uint32_t) &kvmm_boot_first_page_table - KERNEL_VIRTUAL_BASE;
    uint32_t page_dir_phys = (uint32_t) &kvmm_boot_page_directory - KERNEL_VIRTUAL_BASE;
    page_directory_t *boot_pd_phys = (page_directory_t *) page_dir_phys;
    page_table_t *boot_pt_phys = (page_table_t *) page_table_phys;

    kmemset(boot_pd_phys, 0, sizeof(kvmm_boot_page_directory));
    kmemset(boot_pt_phys, 0, sizeof(kvmm_boot_first_page_table));
    for (uint32_t i = 0; i < 1024; i++) {
        boot_pt_phys->_entries[i]._present = 1;
        boot_pt_phys->_entries[i]._rw = 1;
        boot_pt_phys->_entries[i]._frame = i;
    }
    boot_pd_phys->_entries[0]._present = 1;
    boot_pd_phys->_entries[0]._rw = 1;
    boot_pd_phys->_entries[0]._table_addr = page_table_phys >> 12;
    boot_pd_phys->_entries[KERNEL_PD_INDEX]._present = 1;
    boot_pd_phys->_entries[KERNEL_PD_INDEX]._rw = 1;
    boot_pd_phys->_entries[KERNEL_PD_INDEX]._table_addr = page_table_phys >> 12;
    kmmu_load_cr3(page_dir_phys);
    kmmu_enable_paging();
    return OK_TRUE;
}
