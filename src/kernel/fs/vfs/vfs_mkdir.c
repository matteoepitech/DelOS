/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_mkdir
** File description:
** VFS mkdir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Create a directory in a parent node.
 *
 * @param parent     The parent of the directory (likely a dir)
 * @param name       The name of the directory we want to mkdir
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_mkdir(vfs_node_t *parent, const char *name)
{
    if (parent == NULL || name == NULL) {
        return KO_FALSE;
    }
    return parent->_ops->_mkdir(parent, name);
}
