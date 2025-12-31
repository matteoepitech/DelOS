/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_lookup
** File description:
** TMPFS lookup source file
*/

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
    KPRINTF_DEBUG("lookup from ktmpfs driver");
    return NULL;
}
