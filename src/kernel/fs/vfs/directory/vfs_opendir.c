/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/directory/vfs_opendir
** File description:
** VFS opendir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_dir.h>
#include <utils/misc/print.h>

/**
 * @brief Open a directory and get a structure which act like an iterator.
 *
 * @param path   The path to the directory to open
 *
 * @return The directory structure of the concerned path.
 */
vfs_dir_t *
kvfs_opendir(const char *path)
{
    vfs_node_t *dir_node = NULL;
    vfs_dir_t *dir = NULL;

    if (path == NULL) {
        return NULL;
    }
    dir_node = kvfs_open(path);
    if (dir_node->_type != KVFS_DIR) {
        KPRINTF_ERROR("vfs: cannot open this directory: %s", path);
        kvfs_close(dir_node);
        return NULL;
    }
    dir = kcalloc(sizeof(vfs_dir_t));
    if (dir == NULL) {
        return NULL;
    }
    dir->_dir_node = dir_node;
    return dir;
}
