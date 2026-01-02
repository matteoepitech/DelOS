/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/operations/vfs_rmdir
** File description:
** VFS rmdir source file
*/

#include <kernel/fs/vfs/vfs.h>
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
    vfs_node_t *node = NULL;

    if (path == NULL) {
        return KO_FALSE;
    }
    node = kvfs_open(path);
    if (node == NULL) {
        return KO_FALSE;
    }
    if (node->_ops->_rmdir(node) == KO_FALSE) {
        KPRINTF_ERROR("vfs: error while removing a directory");
        return KO_FALSE;
    }
    kvfs_close(node);
    return OK_TRUE;
}
