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
    vfs_node_t *tmp = NULL;
    bool32_t is_absolute = KO_FALSE;
    uint32_t start_idx = 0;

    if (argc < 2) {
        KPRINTF_ERROR("%s", "usage: mkdir <path>");
        return OK_TRUE;
    }
    path_parts_count = kvfs_split_path(argv[1], path_parts);
    is_absolute = kvfs_is_absolute_path(argv[1]);
    node = is_absolute ? kvfs_root_mount_dir : kvfs_cwd;
    start_idx = is_absolute ? 1 : 0;
    if (node == NULL || path_parts_count <= start_idx) {
        KPRINTF_ERROR("%s", "mkdir: invalid path");
        return OK_TRUE;
    }
    for (uint32_t i = start_idx; i < path_parts_count - 1; i++) {
        node = node->_ops->_lookup(node, path_parts[i]);
        if (node == NULL) {
            KPRINTF_ERROR("mkdir: no such file or directory called %s", path_parts[i]);
            return OK_TRUE;
        }
        if (node->_type != KVFS_DIR) {
            KPRINTF_ERROR("mkdir: not a directory %s", path_parts[i]);
            return OK_TRUE;
        }
    }
    tmp = node->_ops->_lookup(node, path_parts[path_parts_count - 1]);
    if (tmp != NULL) {
        kvfs_close(tmp);
        KPRINTF_ERROR("%s", "mkdir: file already exists");
        return OK_TRUE;
    }
    node->_ops->_mkdir(node, path_parts[path_parts_count - 1]);
    return KO_FALSE;
}
