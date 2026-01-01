/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/directory/vfs_readdir
** File description:
** VFS readdir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_dir.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Read one entry of a directory structure. And move the iterator.
 *
 * @param dir    The directory structure (not a dirent)
 *
 * @return The structure of a directory entry.
 */
vfs_dirent_t *
kvfs_readdir(vfs_dir_t *dir)
{
    vfs_dirent_t *dirent = NULL;

    if (dir == NULL) {
        return NULL;
    }
    dirent = kmalloc(sizeof(vfs_dirent_t));
    if (dirent == NULL) {
        return NULL;
    }
    if (dir->_dir_node->_ops->_readdir(dir->_dir_node, dir->_index, dirent) == KO_FALSE) {
        kfree(dirent);
        return NULL;
    }
    dir->_index++;
    return dirent;
}
