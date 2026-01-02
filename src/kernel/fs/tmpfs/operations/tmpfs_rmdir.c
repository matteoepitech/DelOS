/*
** DELOS PROJECT, 2026
** src/kernel/fs/tmpfs/operations/tmpfs_rmdir
** File description:
** TMPFS rmdir source file
*/

#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Remove a directory only and only when its content is empty.
 *
 * @param dir    The directory VFS node to delete
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_rmdir(vfs_node_t *dir)
{
    tmpfs_entry_t *entry = NULL;

    if (dir == NULL) {
        return KO_FALSE;
    }
    entry = dir->_private;
    if (entry == NULL || entry->_parent == NULL) {
        return KO_FALSE;
    }
    if (entry->_dir._child != NULL) {
        return KO_FALSE;
    }
    return ktmpfs_remove_from_parent_ll(entry->_parent, entry);
}
