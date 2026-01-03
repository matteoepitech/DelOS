/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_helper
** File description:
** VFS stat helper source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Create an empty stat structure without any specific file related stuff.
 *
 * @param mode   The least value we need to have is its mode.
 *
 * @return The structure stat.
 */
vfs_stat_t
kvfs_stat_create(mode_t mode)
{
    vfs_stat_t stat_buffer = {0};

    kvfs_stat_update_atime(&stat_buffer);
    kvfs_stat_update_mtime(&stat_buffer);
    kvfs_stat_chmod(&stat_buffer, mode);
    if (KVFS_STAT_ISDIR(mode) == OK_TRUE) {
        kvfs_stat_set_nlink(&stat_buffer, 2);
    } else {
        kvfs_stat_set_nlink(&stat_buffer, 1);
    }
    return stat_buffer;
}

/**
 * @brief Get the stat of a file using node.
 *
 * @param node   The node of the VFS file
 * @param out    The struct buffer pointer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_get_stat(vfs_node_t *node, vfs_stat_t *out)
{
    if (node == NULL || node->_ops == NULL || node->_ops->_stat == NULL || out == NULL) {
        return KO_FALSE;
    }
    return node->_ops->_stat(node, out);
}
