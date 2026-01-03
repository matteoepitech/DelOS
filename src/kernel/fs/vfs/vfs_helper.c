/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_helper
** File description:
** VFS helper source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/fs/vfs/vfs.h>

/* @brief Variable for kernel space "current working directory" (should be root at start time) */
vfs_node_t *kvfs_cwd = NULL;

/**
 * @brief Give us the pointer to the literal string of a type node name.
 *
 * @param mode   The mode of the entry
 *
 * @return The pointer to the literal string 
 */
char *
kvfs_get_type_string(mode_t mode)
{
    if (KVFS_STAT_ISDIR(mode)) {
        return "directory";
    } else if (KVFS_STAT_ISREG(mode)) {
        return "file";
    }
    return "?";
}

/**
 * @brief Split an entire path into some tokens for easier parsing.
 *
 * @param path           The path to split
 * @param tokens         The buffer of tokens (need to be pre-allocated)
 *
 * @return Number of part got.
 */
size_t
kvfs_split_path(const char *path, char tokens[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN])
{
    size_t count = 0;
    size_t i = 0;

    if (!path || KVFS_MAX_PATH_PARTS == 0) {
        return 0;
    }
    bool32_t is_absolute = kvfs_is_absolute_path(path);
    if (is_absolute) {
        if (count >= KVFS_MAX_PATH_PARTS) {
            return count;
        }
        tokens[count][0] = '/';
        tokens[count][1] = '\0';
        count++;
    }
    while (path[i] == '/') {
        i++;
    }
    while (path[i] != '\0' && count < KVFS_MAX_PATH_PARTS) {
        size_t j = 0;

        while (path[i] != '/' && path[i] != '\0' && j < KVFS_MAX_NAME_LEN - 1) {
            tokens[count][j] = path[i];
            j++;
            i++;
        }
        tokens[count][j] = '\0';
        if (j > 0) {
            count++;
        }
        while (path[i] == '/') {
            i++;
        }
    }
    return count;
}

/**
 * @brief Check if a path is absolute or relative.
 *
 * @param path   The path to check
 *
 * @return OK_TRUE if absolute, KO_FALSE otherwise.
 */
bool32_t
kvfs_is_absolute_path(const char *path)
{
    if (path == NULL) {
        return KO_FALSE;
    }
    if (path[0] != '/') {
        return KO_FALSE;
    }
    return OK_TRUE;
}

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
 * @brief Resolve the parent of a file using path.
 *
 * @param start      The start to check
 * @param path       The path to resolve
 * @param out_name   A buffer to stock the name of the final part on the path (used for creation e.g.) (nullable)
 *
 * @return The node of the parent.
 */
vfs_node_t *
kvfs_resolve_parent_from(vfs_node_t *start, const char *path, char *out_name)
{
    char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN] = {0};
    vfs_node_t *prev_node = NULL;
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
    part_index = (path_parts[0][0] == '/') ? 1 : 0;
    if (out_name != NULL) {
        kstrcpy(out_name, path_parts[count_part - 1]);
    }
    tmp_node = start;
    for (uint32_t i = part_index; i < count_part - 1; i++) {
        prev_node = tmp_node;
        tmp_node = kvfs_lookup(tmp_node, path_parts[i]);
        if (prev_node != start) {
            kvfs_close(prev_node);
        }
        if (tmp_node == NULL) {
            return NULL;
        }
    }
    return tmp_node;
}
