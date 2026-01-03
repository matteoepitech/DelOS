/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/directory/vfs_opendir
** File description:
** VFS opendir source file
*/

#include "defines.h"
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
    vfs_stat_t stat_buffer = {0};
    vfs_node_t *dir_node = NULL;
    vfs_dir_t *dir = NULL;

    if (path == NULL) {
        return NULL;
    }
    dir_node = kvfs_open(path);
    if (dir_node == NULL) {
        KPRINTF_ERROR("vfs: cannot open this directory: %s", path);
        return NULL;
    }
    if (dir_node->_ops->_stat(dir_node, &stat_buffer) == KO_FALSE) {
        kvfs_close(dir_node);
        return KO_FALSE;
    }
    if (KVFS_STAT_ISDIR(stat_buffer._mode) == KO_FALSE) {
        KPRINTF_ERROR("vfs: not a directory: %s", path);
        kvfs_close(dir_node);
        return NULL;
    }
    dir = kcalloc(sizeof(vfs_dir_t));
    if (dir == NULL) {
        kvfs_close(dir_node);
        return NULL;
    }
    dir->_dir_node = dir_node;
    return dir;
}

/**
 * @brief Open a directory and get a structure which act like an iterator.
 *        VFS node version. (it does a copy since the node is in the directory structure).
 *        If you closedir the node will be closed so that why we have a copy here.
 *
 * @param node   The node to open dir (will no be close after that since it does copy)
 *
 * @return The directory structure of the concerned path.
 */
vfs_dir_t *
kvfs_opendir_from_node(vfs_node_t *node)
{
    vfs_stat_t stat_buffer = {0};
    vfs_node_t *dir_node = NULL;
    vfs_dir_t *dir = NULL;

    if (node == NULL) {
        return NULL;
    }
    dir_node = node->_ops->_lookup(node, ".");
    if (dir_node == NULL) {
        return NULL;
    }
    if (dir_node->_ops->_stat(dir_node, &stat_buffer) == KO_FALSE) {
        kvfs_close(dir_node);
        return KO_FALSE;
    }
    if (KVFS_STAT_ISDIR(stat_buffer._mode) == KO_FALSE) {
        KPRINTF_ERROR("vfs: not a directory: %s", "no path given (opendir from node)");
        kvfs_close(dir_node);
        return NULL;
    }
    dir = kcalloc(sizeof(vfs_dir_t));
    if (dir == NULL) {
        kvfs_close(dir_node);
        return NULL;
    }
    dir->_dir_node = dir_node;
    return dir;
}
