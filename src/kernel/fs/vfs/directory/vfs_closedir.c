/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/directory/vfs_closedir
** File description:
** VFS close dir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_dir.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Close a directory iterator.
 *        Will free the node contained in and the structure itself.
 *
 * @param dir    The directory structure to close
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_closedir(vfs_dir_t *dir)
{
    if (dir == NULL) {
        return KO_FALSE;
    }
    kvfs_close(dir->_dir_node);
    kfree(dir);
    return OK_TRUE;
}
