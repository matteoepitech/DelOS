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
 * @param offset     The offset for reading
 * @param buffer     The buffer to put the data
 * @param len        Number of maximum byte to read
 *
 * @return Number of bytes read on the file.
 */
size_t
kvfs_read(vfs_node_t *node, off_t offset, void *buffer, size_t len)
{
    const cred_t cred = {0, 0};
    vfs_stat_t st = {0};

    if (node == NULL || buffer == NULL || len == 0) {
        return 0;
    }
    if (kvfs_get_stat(node, &st) == KO_FALSE) {
        return 0;
    }
    if (kvfs_stat_can_read(&st, &cred) == KO_FALSE) {
        return 0;
    }
    return node->_ops->_read(node, offset, buffer, len);
}
