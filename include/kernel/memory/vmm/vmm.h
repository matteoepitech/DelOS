/*
** DELOS PROJECT, 2025
** include/kernel/memory/vmm/vmm
** File description:
** VMM header file
*/

#include <defines.h>
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

    #ifndef KERNEL_VIRTUAL_BASE
        #define KERNEL_VIRTUAL_BASE 0xC0000000
    #endif /* ifndef KERNEL_VIRTUAL_BASE */

    #ifndef KERNEL_PD_INDEX
        #define KERNEL_PD_INDEX (KERNEL_VIRTUAL_BASE / (1024 * 4096))
    #endif /* ifndef KERNEL_PD_INDEX */

    #ifndef VMM_TRANSLATION
        #define VIRT_TO_PHYS(addr) ((uint32_t) (addr) - KERNEL_VIRTUAL_BASE)
        #define PHYS_TO_VIRT(addr) ((uint32_t) (addr) + KERNEL_VIRTUAL_BASE)
    #endif /* ifndef VMM_TRANSLATION */

    #ifndef VMM_RECURSIVE_INFO
        #define VMM_RECURSIVE_INFO
        #define VMM_RECURSIVE_PD_ADDR 0xFFFFF000
        #define VMM_RECURSIVE_PT_BASE 0xFFC00000
    #endif /* ifndef VMM_RECURSIVE_INFO */

    #ifndef VMM_GET_PD
        #define VMM_GET_PD ((page_directory_t *) VMM_RECURSIVE_PD_ADDR) // Using the recursive mapping
    #endif /* ifndef VMM_GET_PD */

    #ifndef VMM_GET_PT_VIA_PDE
        #define VMM_GET_PT_VIA_PDE(pd_index) ((page_table_t *) (VMM_RECURSIVE_PT_BASE + (pd_index * 4096))) // Using the recursive mapping
    #endif /* ifndef VMM_GET_PT_VIA_DE */

    #ifndef VMM_FLAGS
        #define VMM_FLAGS
        #define VMM_FLAG_PRESENT   (1u << 0)
        #define VMM_FLAG_READONLY  (0u << 1)
        #define VMM_FLAG_WRITE     (1u << 1)
        #define VMM_FLAG_RW        (1u << 1)
        #define VMM_FLAG_USER      (1u << 2)
        #define VMM_FLAG_KERNEL    (0u << 2)
    #endif /* ifndef VMM_FLAGS */

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

/* @brief The page directory content of the major content of the OS */
extern page_directory_t *kvmm_page_directory;

/* @brief Variables from the linker script to know the size of the kernel for the page mapping */
extern uint32_t __kernel_start;
extern uint32_t __kernel_end;
extern uint32_t __kernel_physical_start;
extern uint32_t __kernel_virtual_start;
extern uint32_t __kernel_size;
extern uint32_t __kernel_size_pages;

/**
 * @brief Init the kvmm 
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_init(void);

/**
 * @brief Disable the identity mapping to use the new CR3 which is the base one.
 *        Address which is virtual and physical at the same time will now be invalidated.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_disable_identity_mapping(void);

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

/**
 * @brief Unmap a virtual address on the page table referenced by it's address.
 *
 * @param vaddr  The address to unmap
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvmm_unmap_page(vaddr_t vaddr);

#endif /* ifndef KERNEL_MEMORY_VMM_H_ */
