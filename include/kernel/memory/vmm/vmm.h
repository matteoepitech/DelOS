/*
** DELOS PROJECT, 2025
** include/kernel/memory/vmm/vmm
** File description:
** VMM header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_VMM_H_
    #define KERNEL_MEMORY_VMM_H_

// Structure of a virtual address:
//
// 31........22 | 21........12 | 11......0
// PDE index    |   PTE index  |  offset

#ifndef VMM_GET_PDE_INDEX
    #define VMM_GET_PDE_INDEX(vaddr) ((vaddr >> 22) & 0x3FF)
#endif /* ifndef VMM_GET_PDE_INDEX */

#ifndef VMM_GET_PTE_INDEX
    #define VMM_GET_PTE_INDEX(vaddr) ((vaddr >> 12) & 0x3FF)
#endif /* ifndef VMM_GET_PTE_INDEX */

#ifndef VMM_GET_OFFSET_VAL
    #define VMM_GET_OFFSET_VAL(vaddr) (vaddr & 0xFFF)
#endif /* ifndef VMM_GET_OFFSET_VAL */

/* @brief The address type for a virtual address space */
typedef uint32_t vaddr_t;
/* @brief The address type for a physical address space */
typedef uint32_t paddr_t;

/*
 * @brief Definition of a page table entry structure.
 *        More information here : https://wiki.osdev.org/Paging
 */
typedef struct page_table_entry_s {
    uint32_t _present : 1;
    uint32_t _rw : 1;
    uint32_t _user : 1;
    uint32_t _write_through : 1;
    uint32_t _cache_disable : 1;
    uint32_t _accessed : 1;
    uint32_t _dirty : 1;
    uint32_t _pat : 1;
    uint32_t _global : 1;
    uint32_t _available : 3;
    uint32_t _frame : 20;
} page_table_entry_t;

/*
 * @brief Definition of a page table. A page table contains 1024 entries.
 */
typedef struct page_table_s {
    page_table_entry_t _entries[1024];
} page_table_t;

/*
 * @brief Definition of a page directory table entry structure.
 *        More information here : https://wiki.osdev.org/Paging
 */
typedef struct {
    uint32_t _present : 1;
    uint32_t _rw : 1;
    uint32_t _user : 1;
    uint32_t _write_through : 1;
    uint32_t _cache_disable : 1;
    uint32_t _accessed : 1;
    uint32_t _reserved : 1;
    uint32_t _page_size : 1;
    uint32_t _ignored : 1;
    uint32_t _available : 3;
    uint32_t _table_addr : 20;
} page_directory_entry_t;

/*
 * @brief Definition of a page directory. A page directory contains 1024 entries.
 */
typedef struct {
    page_directory_entry_t _entries[1024];
} page_directory_t;

/* @brief The page directory content */
extern page_directory_t kvmm_page_directory;

/**
 * @brief Init the kvmm 
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_init(void);

/**
 * @brief Map a virtual address to a physical address.
 *
 * @param vaddr  The virtual address
 * @param paddr  The physical address
 * @param flags  Some flags
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_map_page(vaddr_t vaddr, paddr_t paddr, uint32_t flags);

#endif /* ifndef KERNEL_MEMORY_VMM_H_ */
