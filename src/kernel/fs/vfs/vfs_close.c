/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_close
** File description:
** VFS close source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Close a VFS node, if the refcount is zeroed then destroying it.
 *
 * @param node   The VFS node to close
 */
void
kvfs_close(vfs_node_t *node)
{
    if (node == NULL || node == kvfs_root_mount_dir) {
        return;
    }
    if (node->_refcount == 0) {
        return;
    }
    node->_refcount--;
    if (node->_refcount == 0) {
        kfree(node);
    }
}
