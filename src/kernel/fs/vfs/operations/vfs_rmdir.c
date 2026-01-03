/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/operations/vfs_rmdir
** File description:
** VFS rmdir source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Remove a directory at a given path.
 *
 * @param path   The path of the directory to remove
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_rmdir(const char *path)
{
    const cred_t cred = {0, 0};
    vfs_node_t *node = NULL;
    vfs_stat_t st = {0};

    if (path == NULL) {
        return KO_FALSE;
    }
    node = kvfs_lookup_open(path);
    if (node == NULL) {
        return KO_FALSE;
    }
    if (kvfs_get_stat(node, &st) == KO_FALSE) {
        kvfs_close(node);
        return KO_FALSE;
    }
    if (kvfs_stat_can_write(&st, &cred) == KO_FALSE) {
        kvfs_close(node);
        return KO_FALSE;
    }
    if (KVFS_STAT_ISDIR(st._mode) == KO_FALSE) {
        KPRINTF_ERROR("vfs: this file is not a directory");
        return KO_FALSE;
    }
    if (node->_ops->_rmdir(node) == KO_FALSE) {
        KPRINTF_ERROR("vfs: error while removing a directory");
        return KO_FALSE;
    }
    kvfs_close(node);
    return OK_TRUE;
}
