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
    ktmpfs_lookup,
    ktmpfs_create,
    ktmpfs_mkdir,
    ktmpfs_rmdir,
    ktmpfs_readdir,
    ktmpfs_unlink
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
 * @brief Convert a file type from TMPFS into VFS type.
 *
 * @param type   The type to convert (tmpfs file type specific)
 *
 * @return The final type of VFS node type.
 */
vfs_node_type_t
ktmpfs_convert_vfs_node_type(tmpfs_file_type_t type)
{
    switch (type) {
        case KTMPFS_DIR:
            return KVFS_DIR;
        default:
        case KTMPFS_FILE:
            return KVFS_FILE;
    }
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
    node->_type = ktmpfs_convert_vfs_node_type(entry->_type);
    node->_size = entry->_file._size;
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

/**
 * @brief Remove the entry from the parent linked list childs.
 *
 * @param parent     The pointer to the parent of that entry
 * @param entry      The pointer to the entry to remove
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_remove_from_parent_ll(tmpfs_entry_t *parent, tmpfs_entry_t *entry)
{
    tmpfs_entry_t *prev = NULL;
    tmpfs_entry_t *tmp = NULL;

    if (parent == NULL || entry == NULL) {
        return KO_FALSE;
    }
    tmp = parent->_dir._child;
    while (tmp != entry && tmp != NULL) {
        prev = tmp;
        tmp = tmp->_next;
    }
    if (tmp == NULL) {
        return KO_FALSE;
    }
    if (prev == NULL) {
        parent->_dir._child = tmp->_next;
    } else {
        prev->_next = tmp->_next;
    }
    kfree(tmp);
    return OK_TRUE;
}
