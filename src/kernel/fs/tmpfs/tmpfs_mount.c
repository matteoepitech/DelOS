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
 * @return The entry pointer created, NULL otherwise.
 */
static tmpfs_entry_t *
create_root_entry(void)
{
    tmpfs_entry_t *root_entry = kmalloc(sizeof(tmpfs_entry_t));

    if (root_entry == NULL) {
        return NULL;
    }
    if (kstrcpy(root_entry->_name, "/") == NULL) {
        kfree(root_entry);
        return NULL;
    }
    root_entry->_parent = NULL;
    root_entry->_next = NULL;
    root_entry->_type = KTMPFS_DIR;
    root_entry->_dir._child = NULL;
    return root_entry;
}

/**
 * @brief Create the root vfs node using the created entry on that tmpfs.
 *
 * @param root_entry     The root entry already created
 *
 * @return The vfs node pointer created or NULL otherwise.
 */
static vfs_node_t *
create_root_vfs_node(tmpfs_entry_t *root_entry)
{
    vfs_node_t *root_node = kmalloc(sizeof(vfs_node_t));
    vfs_fs_t *fs = kvfs_get_fs("tmpfs");

    if (root_node == NULL || fs == NULL) {
        return NULL;
    }
    root_node->_fs = fs;
    root_node->_ops = ktmpfs_get_operations();
    root_node->_private = root_entry;
    root_node->_refcount = 1;
    root_node->_type = KVFS_DIR;
    root_node->_size = 0;
    return root_node;
}

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
    tmpfs_entry_t *root_entry = NULL;
    vfs_node_t *root_node = NULL;

    root_entry = create_root_entry();
    if (root_entry == NULL) {
        return NULL;
    }
    root_node = create_root_vfs_node(root_entry);
    if (root_node == NULL) {
        kfree(root_entry);
        return NULL;
    }
    return root_node;
}
