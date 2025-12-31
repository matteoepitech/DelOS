/*
** DELOS PROJECT, 2025
** include/kernel/fs/tmpfs/tmpfs
** File description:
** TMPFS header file
*/

#include <defines.h>
#include <types.h>

#ifndef KERNEL_FS_TMPFS_H_
    #define KERNEL_FS_TMPFS_H_

    #ifndef KTMPFS_NAME_MAX_LEN
        #define KTMPFS_NAME_MAX_LEN 64 
    #endif /* ifndef KTMPFS_NAME_MAX_LEN */

/*
 * @brief This enumeration contains all differents type of a file for the TMPFS.
 */
typedef enum {
    TMPFS_FILE,
    TMPFS_DIR,
} tmpfs_file_type_t;

/*
 * @brief Structure for a file entry in the tmpfs file system.
 *        - name     = the name of the entry (max len KTMPFS_NAME_MAX_LEN)
 *        - type     = the type of the entry
 *        - parent   = the parent of the entry (likely a dir)
 *        - data_ptr = the pointer to the raw data in memory (file type)
 *        - size     = the size of the raw data in memory (file type)
 *        - child    = the first child entry of a dir (dir type) then use the next to go through entire dir
 *        - next     = the next occurence in the entry (on a dir for example)
 */
typedef struct tmpfs_entry_s {
    char _name[KTMPFS_NAME_MAX_LEN];
    tmpfs_file_type_t _type;
    struct tmpfs_entry_s *_parent;
    union {
        struct {
            uint8_t *_data_ptr;
            size_t _size;
        } _file;
        struct {
            struct tmpfs_entry_s *_child;
        } _dir;
    };
    struct tmpfs_entry_s *_next;
} tmpfs_entry_t;

#endif /* ifndef KERNEL_FS_TMPFS_H_ */
