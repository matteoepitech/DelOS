/*
** DELOS PROJECT, 2026
** include/kernel/fs/fd/fd
** File description:
** FD header file
*/

#include <kernel/fs/vfs/vfs.h>
#include <types.h>

#ifndef KERNEL_FS_FD_H_
    #define KERNEL_FS_FD_H_

    #ifndef KFD_MAX_COUNT
        #define KFD_MAX_COUNT 32
    #endif /* ifndef KFD_MAX_COUNT */

    #ifndef KFD_ERROR
        #define KFD_ERROR -1 
    #endif /* ifndef KFD_ERROR */

/*
 * @brief Structure for a file descriptor.
 *        - node     = the VFS node
 *        - offset   = the current offset to the file
 *        - flags    = the flags
 *        - refcount = the reference count
 */
typedef struct file_desc_s {
    vfs_node_t *_node;
    off_t _offset;
    uint32_t _flags;
    uint32_t _refcount;
} file_desc_t;

/* @brief TEMPORARY variable to store file descriptors */
extern file_desc_t *kfd_table[KFD_MAX_COUNT];

/**
 * @brief Create a file descriptor from a VFS node.
 *
 * @param node   The VFS node
 *
 * @return The file descriptor created from the node.
 */
fd_t
kfd_create(vfs_node_t *node);

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 * @param flags  The flags O_CREAT | O_RDONLY ...
 * @param mode   The mode (used when creating the file only)
 *
 * @return The file descriptor.
 */
fd_t
kfd_open(const char *path, int32_t flags, mode_t mode);

#endif /* ifndef KERNEL_FS_FD_H_ */
