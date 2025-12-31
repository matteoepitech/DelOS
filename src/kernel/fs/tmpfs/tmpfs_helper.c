/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_helper
** File description:
** TMPFS helper source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/* @brief Variable containing a static version of all operations of TMPFS fs */
vfs_ops_t ktmpfs_operations = {
    ktmpfs_read,
    ktmpfs_write,
    ktmpfs_lookup
};

/**
 * @brief Get the structure containing every callback for that filesystem.
 *
 * @return Pointer to the vfs_ops_t structure for the TMPFS fs.
 */
vfs_ops_t *
ktmpfs_get_operations(void)
{
    return &ktmpfs_operations;
}

/**
 * @brief Create a VFS node using an entry on that tmpfs.
 *
 * @param entry     The entry to get data from
 *
 * @return The VFS node pointer created or NULL otherwise.
 */
vfs_node_t *
ktmpfs_create_vfs_node(tmpfs_entry_t *entry)
{
    vfs_node_t *node = NULL;
    vfs_fs_t *fs = NULL;

    if (entry == NULL) {
        return NULL;
    }
    node = kmalloc(sizeof(vfs_node_t));
    fs = kvfs_get_fs("tmpfs");
    if (node == NULL || fs == NULL) {
        return NULL;
    }
    node->_fs = fs;
    node->_ops = ktmpfs_get_operations();
    node->_private = entry;
    node->_refcount = 1;
    node->_type = entry->_type == KTMPFS_FILE ? KVFS_FILE : KVFS_DIR;
    node->_size = 0;
    return node;
}
