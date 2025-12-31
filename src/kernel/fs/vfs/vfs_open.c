/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_open
** File description:
** VFS open source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_open(char *path)
{
    char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN] = {0};
    vfs_node_t *tmp_node = NULL;
    uint32_t count_part = 0;

    if (path == NULL) {
        return NULL;
    }
    count_part = kvfs_split_path(path, path_parts);
    if (count_part == 0) {
        return NULL;
    }
    if (kstrcmp(path_parts[0], "/") == 0) {
        tmp_node = NULL; // TODO: Get the root node
    } else {
        KPRINTF_ERROR("vfs: opening file without absolute path is not handled yet");
        return NULL; // TODO: ?
    }
    for (uint32_t i = 1; i < count_part; i++) {
        tmp_node = kvfs_lookup(tmp_node, path_parts[i]);
    }
    return tmp_node;
}
