/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/operations/vfs_write
** File description:
** VFS write source file
*/

#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Write some data in a file.
 *
 * @param node       The node where to write the data
 * @param buffer     The buffer to take the data from
 * @param len        Number of maximum byte to write
 *
 * @return Number of bytes write on the file.
 */
size_t
kvfs_write(vfs_node_t *node, const void *buffer, size_t len)
{
    // TODO: do the offset, need file descriptors for that
    if (node == NULL || buffer == NULL || len == 0) {
        return 0;
    }
    return node->_ops->_write(node, 0, buffer, len);
}
