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
 * @param offset     The offset pointer for writing
 * @param buffer     The buffer to take the data from
 * @param len        Number of maximum byte to write
 *
 * @return Number of bytes write on the file.
 */
size_t
kvfs_write(vfs_node_t *node, off_t *offset, const void *buffer, size_t len)
{
    const cred_t cred = {0, 0};
    vfs_stat_t st = {0};

    if (node == NULL || buffer == NULL || len == 0) {
        return 0;
    }
    if (kvfs_get_stat(node, &st) == KO_FALSE) {
        return 0;
    }
    if (kvfs_stat_can_write(&st, &cred) == KO_FALSE) {
        return 0;
    }
    return node->_ops->_write(node, offset, buffer, len);
}
