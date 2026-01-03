/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/operations/vfs_unlink
** File description:
** VFS unlink source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <utils/misc/print.h>
#include <defines.h>
#include <types.h>
    
/**
 * @brief Unlink a file (remove it's entry but not his data of course)
 *
 * @param path   The path to the file to unlink
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_unlink(const char *path)
{
    const cred_t cred = {0, 0};
    vfs_node_t *node = NULL;
    vfs_stat_t st = {0};

    if (path == NULL) {
        return KO_FALSE;
    }
    node = kvfs_lookup_open(path);
    if (node == NULL) {
        KPRINTF_ERROR("vfs: no such file or directory to unlink");
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
    if (KVFS_STAT_ISREG(st._mode) == KO_FALSE) {
        KPRINTF_ERROR("vfs: cannot unlink this type of file");
        return KO_FALSE;
    }
    if (node->_ops->_unlink(node) == KO_FALSE) {
        KPRINTF_ERROR("vfs: error while unlinking the file in fs operation");
        return KO_FALSE;
    }
    kvfs_close(node);
    return OK_TRUE;
}
