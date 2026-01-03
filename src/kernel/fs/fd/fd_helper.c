/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/fd_helper
** File description:
** FD helper source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/fd/fd.h>

/* @brief TEMPORARY variable to store file descriptors */
file_desc_t *kfd_table[KFD_MAX_COUNT] = {NULL};

/**
 * @brief Create a file descriptor from a VFS node.
 *
 * @param node   The VFS node
 *
 * @return The file descriptor created from the node.
 */
fd_t
kfd_create(vfs_node_t *node)
{
    file_desc_t *fd_struct = NULL;
    fd_t fd = KFD_ERROR;

    if (node == NULL) {
        return KFD_ERROR;
    }
    for (fd = 0; fd < KFD_MAX_COUNT; fd++) {
        if (kfd_table[fd] == NULL) {
            break;
        }
    }
    if (fd >= KFD_MAX_COUNT) {
        return KFD_ERROR;
    }
    fd_struct = kmalloc(sizeof(file_desc_t));
    if (fd_struct == NULL) {
        return KFD_ERROR;
    }
    fd_struct->_node = node;
    fd_struct->_offset = 0;
    fd_struct->_flags = 0;
    fd_struct->_refcount = 1;
    kfd_table[fd] = fd_struct;
    return fd;
}
