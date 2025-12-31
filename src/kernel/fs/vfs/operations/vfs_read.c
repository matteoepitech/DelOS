/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/operations/vfs_read
** File description:
** VFS read source file
*/

#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Read some data from a file.
 *
 * @param node       The node where to read the data
 * @param buffer     The buffer to put the data
 * @param len        Number of maximum byte to read
 *
 * @return Number of bytes read on the file.
 */
size_t
kvfs_read(vfs_node_t *node, void *buffer, size_t len)
{
    // TODO: do the offset, need file descriptors for that
    if (node == NULL || buffer == NULL || len == 0) {
        return 0;
    }
    return node->_ops->_read(node, 0, buffer, len);
}
