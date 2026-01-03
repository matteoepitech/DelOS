/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/mkdir
** File description:
** mkdir command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Validate arguments and split a path into parts.
 *
 * @param argc               Number of arguments given to the command
 * @param argv               Array of arguments
 * @param path_parts         Output buffer for splitted path components
 * @param path_parts_count   Output count of path components
 * @param is_absolute        Output flag set if the path is absolute
 *
 * @return OK_TRUE on success, KO_FALSE on invalid input.
 */
static bool32_t
validate_and_split_path(uint32_t argc, char *argv[], char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN], uint32_t *path_parts_count, bool32_t *is_absolute)
{
    if (argc < 2) {
        KPRINTF_ERROR("%s", "usage: mkdir <path>");
        return KO_FALSE;
    }
    *path_parts_count = kvfs_split_path(argv[1], path_parts);
    *is_absolute = kvfs_is_absolute_path(argv[1]);
    if (*path_parts_count == 0) {
        KPRINTF_ERROR("%s", "mkdir: invalid path");
        return KO_FALSE;
    }
    return OK_TRUE;
}

/**
 * @brief Resolve and return the parent node of the target directory to create.
 *
 * @param start              Starting VFS node (cwd or root)
 * @param path_parts         Splitted path components
 * @param path_parts_count   Number of path components
 * @param start_idx          Index to start processing (skip root marker when absolute)
 *
 * @return Parent node pointer on success, NULL on error.
 */
static vfs_node_t *
resolve_parent_node(vfs_node_t *start, char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN], uint32_t path_parts_count, uint32_t start_idx)
{
    vfs_stat_t stat_buffer = {0};
    vfs_node_t *next = NULL;
    vfs_node_t *free = NULL;

    for (uint32_t i = start_idx; i < path_parts_count - 1; i++) {
        next = kvfs_lookup(start, path_parts[i]);
        if (free != NULL) {
            kvfs_close(free);
        }
        if (next == NULL) {
            KPRINTF_ERROR("mkdir: no such file or directory called %s", path_parts[i]);
            return NULL;
        }
        if (next->_ops->_stat(next, &stat_buffer) == KO_FALSE) {
            kvfs_close(next);
            return NULL;
        }
        if (KVFS_STAT_ISDIR(stat_buffer._mode) == KO_FALSE) {
            KPRINTF_ERROR("mkdir: not a directory %s", path_parts[i]);
            kvfs_close(next);
            return NULL;
        }
        free = next;
        start = next;
    }
    return start;
}

/**
 * @brief Ensure the target directory does not already exist.
 *
 * @param parent       Parent directory VFS node
 * @param target_name  Name of the directory to create
 *
 * @return OK_TRUE if the target is absent, KO_FALSE if it already exists.
 */
static bool32_t
ensure_target_absent(vfs_node_t *parent, const char *target_name)
{
    vfs_node_t *existing = kvfs_lookup(parent, target_name);

    if (existing == NULL) {
        return OK_TRUE;
    }
    kvfs_close(existing);
    KPRINTF_ERROR("%s", "mkdir: file already exists");
    return KO_FALSE;
}

/**
 * @brief Command for mkdir.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_mkdir(uint32_t argc, char *argv[])
{
    char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN] = {0};
    uint32_t path_parts_count = 0;
    vfs_node_t *node = NULL;
    bool32_t is_absolute = KO_FALSE;
    uint32_t start_idx = 0;

    if (validate_and_split_path(argc, argv, path_parts, &path_parts_count, &is_absolute) == KO_FALSE) {
        return OK_TRUE;
    }
    node = is_absolute ? kvfs_root_mount_dir : kvfs_cwd;
    start_idx = is_absolute ? 1 : 0;
    if (node == NULL || path_parts_count <= start_idx) {
        KPRINTF_ERROR("%s", "mkdir: invalid path");
        return OK_TRUE;
    }
    node = resolve_parent_node(node, path_parts, path_parts_count, start_idx);
    if (node == NULL) {
        return OK_TRUE;
    }
    if (ensure_target_absent(node, path_parts[path_parts_count - 1]) == KO_FALSE) {
        return OK_TRUE;
    }
    if (kvfs_mkdir(node, path_parts[path_parts_count - 1]) == KO_FALSE) {
        KPRINTF_ERROR("%s", "mkdir: failed to create directory");
        return OK_TRUE;
    }
    return KO_FALSE;
}
