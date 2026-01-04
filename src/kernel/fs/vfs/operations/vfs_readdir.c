/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/directory/vfs_readdir
** File description:
** VFS readdir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief VFS generic readdir dispatcher.
 *
 * @param node    VFS node (directory)
 * @param offset  Directory offset pointer (owned by fd)
 * @param out     Output directory entry
 *
 * @return OK_TRUE if entry read, KO_FALSE otherwise
 */
bool32_t
kvfs_readdir(vfs_node_t *node, off_t *offset, dirent_t *out)
{
    const cred_t cred = {0, 0};
    vfs_stat_t st = {0};

    if (node == NULL || offset == NULL || out == NULL) {
        return KO_FALSE;
    }
    if (node->_ops == NULL || node->_ops->_readdir == NULL) {
        return KO_FALSE;
    }
    if (kvfs_get_stat(node, &st) == KO_FALSE) {
        return KO_FALSE;
    }
    if (KVFS_STAT_ISDIR(st._mode) == KO_FALSE) {
        return KO_FALSE;
    }
    if (kvfs_stat_can_read(&st, &cred) == KO_FALSE || kvfs_stat_can_exec(&st, &cred) == KO_FALSE) {
        return KO_FALSE;
    }
    return node->_ops->_readdir(node, offset, out);
}
