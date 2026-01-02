/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_lookup
** File description:
** TMPFS lookup source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
    
/**
 * @brief Get another node from the VFS with a node and next level path.
 *
 * @param node           The node of the file in the VFS
 * @param next_level     The next level of the node (e.g. we are at "/" we want the file "abc", next_level = "abc")
 *
 * @return The new VFS node we get in the next level.
 */
vfs_node_t *
ktmpfs_lookup(vfs_node_t *node, const char *next_level)
{
    tmpfs_entry_t *child_entry = NULL;
    tmpfs_entry_t *entry = NULL;

    if (node == NULL || next_level == NULL || node->_private == NULL) {
        return NULL;
    }
    entry = (tmpfs_entry_t *) node->_private;
    if (entry->_type != KTMPFS_DIR) {
        return NULL;
    }
    if (kstrcmp(next_level, ".") == 0) {
        return ktmpfs_create_vfs_node(entry);
    } else if (kstrcmp(next_level, "..") == 0) {
        return ktmpfs_create_vfs_node(entry->_parent == NULL ? entry : entry->_parent);
    }
    child_entry = entry->_dir._child;
    while (child_entry != NULL && kstrcmp(child_entry->_name, next_level) != 0) {
        child_entry = child_entry->_next;
    }
    return ktmpfs_create_vfs_node(child_entry);
}
