/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_mount
** File description:
** TMPFS mount source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Create the vfs node and tmpfs entry for the root directory.
 *
 * @param device    The device pointer on how to access data (unused on tmpfs)
 *
 * @return The root directory of the tmpfs file system ("/").
 */
vfs_node_t *
ktmpfs_mount(UNUSED void *device)
{
    tmpfs_entry_t *root_entry = kmalloc(sizeof(tmpfs_entry_t));

    if (kstrcpy(root_entry->_name, "/") == NULL) {
        kfree(root_entry);
        return NULL;
    }
    root_entry->_parent = NULL;
    root_entry->_next = NULL;
    root_entry->_type = KTMPFS_DIR;
    root_entry->_dir._child = NULL;
}
