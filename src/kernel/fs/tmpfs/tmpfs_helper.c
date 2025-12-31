/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_helper
** File description:
** TMPFS helper source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/misc/panic.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

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
    KPRINTF_DEBUG("CREATED");
    return node;
}

/**
 * @brief Create an entry on the TMPFS fs using parent, name, type and return it.
 *
 * @param parent     The parent of the entry
 * @param name       The name of the entry
 * @param type       The type of the entry
 *
 * @return The entry created.
 */
tmpfs_entry_t *
ktmpfs_create_entry(tmpfs_entry_t *parent, const char *name, tmpfs_file_type_t type)
{
    tmpfs_entry_t *entry = NULL;

    if (parent == NULL || name == NULL || parent->_type != KTMPFS_DIR) {
        return NULL;
    }
    if (type != KTMPFS_DIR && type != KTMPFS_FILE) {
        KPANIC("Trying to create a file using an unknown type on a TMPFS file system.");
        return NULL;
    }
    entry = kmalloc(sizeof(tmpfs_entry_t));
    if (entry == NULL) {
        return NULL;
    }
    kstrcpy(entry->_name, name);
    entry->_next = parent->_dir._child;
    parent->_dir._child = entry;
    entry->_parent = parent;
    entry->_type = type;
    switch (type) {
        case KTMPFS_DIR:
            entry->_dir._child = NULL;
            break;
        case KTMPFS_FILE:
            entry->_file._data_ptr = NULL;
            entry->_file._size = 0;
            break;
    }
    return entry;
}
