/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/operations/vfs_stat
** File description:
** VFS stat source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Get metadata using the stat structure of a file or directory or such.
 *
 * @param path       The path of the file to get stat from
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat(const char *path, vfs_stat_t *stat_ptr)
{
    bool32_t res = KO_FALSE;
    vfs_node_t *node = NULL;

    if (path == NULL || stat_ptr == NULL) {
        return KO_FALSE;
    }
    node = kvfs_open(path);
    if (node == NULL) {
        KPRINTF_ERROR("vfs: cannot open file to get stat metadata");
        return KO_FALSE;
    }
    res = node->_ops->_stat(node, stat_ptr);
    kvfs_close(node);
    return res;
}

/**
 * @brief Get metadata using the stat structure of a file or directory or such.
 *
 * @param node       The node of the file to stat (will not be closed or modified)
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat_from_node(vfs_node_t *node, vfs_stat_t *stat_ptr)
{
    bool32_t res = KO_FALSE;

    if (node == NULL || stat_ptr == NULL) {
        return KO_FALSE;
    }
    res = node->_ops->_stat(node, stat_ptr);
    return res;
}
