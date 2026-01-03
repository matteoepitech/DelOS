/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_mount
** File description:
** TMPFS mount source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Create the root entry for the TMPFS.
 *
 * @param loc       The location of the root
 *
 * @return The entry pointer created, NULL otherwise.
 */
static tmpfs_entry_t *
create_root_entry(const char *loc)
{
    tmpfs_entry_t *root_entry = kmalloc(sizeof(tmpfs_entry_t));

    if (root_entry == NULL) {
        return NULL;
    }
    if (kstrcpy(root_entry->_name, loc) == NULL) {
        kfree(root_entry);
        return NULL;
    }
    root_entry->_parent = NULL;
    root_entry->_next = NULL;
    root_entry->_dir._child = NULL;
    root_entry->_stat = kvfs_stat_create(KVFS_STAT_IFDIR);
    return root_entry;
}

/**
 * @brief Create the vfs node and tmpfs entry for the root directory.
 *
 * @param loc       The location of the mount
 * @param device    The device pointer on how to access data (unused on tmpfs)
 *
 * @return The root directory of the tmpfs file system ("/").
 */
vfs_node_t *
ktmpfs_mount(const char *loc, UNUSED void *device)
{
    tmpfs_entry_t *root_entry = NULL;
    vfs_node_t *root_node = NULL;

    root_entry = create_root_entry(loc);
    if (root_entry == NULL) {
        return NULL;
    }
    root_node = ktmpfs_create_vfs_node(root_entry);
    if (root_node == NULL) {
        kfree(root_entry);
        return NULL;
    }
    return root_node;
}
