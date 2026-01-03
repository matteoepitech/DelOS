/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_create
** File description:
** VFS create source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Create a file in a parent node.
 *
 * @param parent     The parent of the file (likely a dir)
 * @param name       The name of the file we want to create
 * @param mode       The mode of the file
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_create(vfs_node_t *parent, const char *name, mode_t mode)
{
    const cred_t cred = {0, 0};
    vfs_stat_t st = {0};

    if (parent == NULL || name == NULL) {
        return KO_FALSE;
    }
    if (kvfs_get_stat(parent, &st) == KO_FALSE) {
        return KO_FALSE;
    }
    if (kvfs_stat_can_write(&st, &cred) == KO_FALSE) {
        return KO_FALSE;
    }
    mode = KVFS_STAT_MODE_MASK_IT(mode) | KVFS_STAT_IFREG;
    return parent->_ops->_create(parent, name, mode);
}
