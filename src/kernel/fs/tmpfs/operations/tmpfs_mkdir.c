/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_mkdir
** File description:
** TMPFS mkdir source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Create a directory in a parent entry on the TMPFS.
 *
 * @param parent     The parent of the dir (likely a dir)
 * @param name       The name of the dir we want to mkdir
 * @param mode       The mode for the directory
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_mkdir(vfs_node_t *parent, const char *name, mode_t mode)
{
    mode = KVFS_STAT_MODE_MASK_IT(mode);
    if (parent == NULL || name == NULL) {
        return KO_FALSE;
    }
    if (ktmpfs_create_entry(parent->_private, name, mode | KVFS_STAT_IFDIR) == NULL) {
        return KO_FALSE;
    }
    kvfs_stat_inc_nlink(&((tmpfs_entry_t *) parent->_private)->_stat);
    return OK_TRUE;
}
