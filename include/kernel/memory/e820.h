/*
** DELOS PROJECT, 2025
** include/kernel/memory/pmm/e820
** File description:
** E820 header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_PMM_E820_H_
    #define KERNEL_MEMORY_PMM_E820_H_
    
    /* e820 data is written by the bootloader in low memory; keep in sync with boot/e820.s */
    #ifndef E820_INFO_ADDR
        #define E820_INFO_ADDR 0x0500
    #endif /* ifndef E820_INFO_ADDR*/

    #ifndef E820_BUFFER_ADDR
        #define E820_BUFFER_ADDR 0x0600
    #endif /* ifndef E820_BUFFER_ADDR*/

    #ifndef E820_ENTRY_SIZE
        #define E820_ENTRY_SIZE 0x18
    #endif /* ifndef E820_ENTRY_SIZE*/

    #ifndef E820_MAX_ENTRIES
        #define E820_MAX_ENTRIES 32
    #endif /* ifndef E820_MAX_ENTRIES */
    /* -- stop syncing here -- */

    #ifndef E820_TYPES
        #define E820_TYPE_FREE 1
        #define E820_TYPE_USED 2
    #endif /* ifndef E820_TYPES */
    
    /* @brief e820 info filled by the bootloader at E820_INFO_ADDR */
    #ifndef E820_INFO
        #define E820_INFO ((volatile e820_memory_info_t *) (E820_INFO_ADDR))
    #endif /* ifndef E820_INFO */

/*
 * @brief The sturcture of an e820 entry.
 *        - base = the base address of the start of the region
 *        - length = the length of the region we are looking at
 *        - type = the type of the region, 1 = free, 2 = used, 3 = ?
 *        - ext = some extended attributes
 */
typedef struct e820_entry_s {
    uint64_t _base;
    uint64_t _length;
    uint32_t _type;
    uint32_t _ext;
} __attribute__((packed)) e820_entry_t;

/*
 * @brief The structure of the e820 informations.
 *        - entries_count = The number of entries got from the BIOS interrupt
 *        - entries_buffer = The buffer address of the start of entries
 */
typedef struct e820_memory_info_s {
    uint32_t _entries_count;
    e820_entry_t *_entries_buffer;
} e820_memory_info_t;

#endif /* ifndef KERNEL_MEMORY_PMM_E820_H_ */
