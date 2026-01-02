/*
** DELOS PROJECT, 2026
** src/kernel/fs/tmpfs/operations/tmpfs_unlink
** File description:
** TMPFS unlink source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Remove the entry from the parent linked list childs.
 *
 * @param parent     The pointer to the parent of that entry
 * @param entry      The pointer to the entry to remove
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
static bool32_t
remove_from_parent_ll(tmpfs_entry_t *parent, tmpfs_entry_t *entry)
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

/**
 * @brief Unlink a file (remove it's entry but not his data of course)
 *
 * @param node   The node to remove its entry
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_unlink(vfs_node_t *node)
{
    tmpfs_entry_t *parent = NULL;
    tmpfs_entry_t *entry = NULL;

    if (node == NULL) {
        return KO_FALSE;
    }
    entry = node->_private;
    parent = entry->_parent;
    return remove_from_parent_ll(parent, entry);
}
