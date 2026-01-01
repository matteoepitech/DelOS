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
    if (dir == NULL || dir->_dir_node == NULL || dir->_dir_node->_ops == NULL || dir->_dir_node->_ops->_readdir == NULL) {
        return NULL;
    }
    if (dir->_dir_node->_ops->_readdir(dir->_dir_node, dir->_index, &dir->_dirent) == KO_FALSE) {
        return NULL;
    }
    dir->_index++;
    return &dir->_dirent;
}
