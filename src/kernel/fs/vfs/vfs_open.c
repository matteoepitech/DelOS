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
 * @brief Resolve and get the VFS node of a relative path using the start.
 *
 * @param start  The start of the resolving, NULL for root
 * @param path   The relative path to a node from the start (e.g. "abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_resolve_from(vfs_node_t *start, const char *path)
{
    char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN] = {0};
    vfs_node_t *free_node = NULL;
    vfs_node_t *tmp_node = NULL;
    uint32_t count_part = 0;
    uint32_t part_index = 0;

    if (path == NULL) {
        return NULL;
    }
    start = kvfs_is_absolute_path(path) || start == NULL ? kvfs_root_mount_dir : start;
    if (start == NULL) {
        return NULL;
    }
    count_part = kvfs_split_path(path, path_parts);
    if (count_part == 0) {
        return NULL;
    }
    part_index = path_parts[0][0] == '/' ? 1 : 0;
    tmp_node = start;
    for (uint32_t i = part_index; i < count_part; i++) {
        free_node = tmp_node;
        tmp_node = kvfs_lookup(tmp_node, path_parts[i]);
        if (free_node != start) {
            kvfs_close(free_node);
        }
        if (tmp_node == NULL) {
            return NULL;
        }
    }
    return tmp_node;
}

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_open(const char *path)
{
    if (path == NULL) {
        return NULL;
    }
    if (path[0] == '/') {
        return kvfs_resolve_from(NULL, path);
    } else {
        return kvfs_resolve_from(kvfs_cwd, path);
    }
}
