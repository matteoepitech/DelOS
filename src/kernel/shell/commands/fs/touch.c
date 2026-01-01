/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/touch
** File description:
** touch command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for touch.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_touch(uint32_t argc, char *argv[])
{
    char path_parts[KVFS_MAX_PATH_PARTS][KVFS_MAX_NAME_LEN] = {0};
    uint32_t path_parts_count = 0;
    vfs_node_t *node = NULL;
    vfs_node_t *tmp = NULL;

    if (argc < 2) {
        KPRINTF_ERROR("%s", "usage: touch <path>");
        return OK_TRUE;
    }
    if (kvfs_is_absolute_path(argv[1]) == KO_FALSE) {
        KPRINTF_ERROR("%s", "touch: only absolute path is supported yet");
        return OK_TRUE;
    }
    path_parts_count = kvfs_split_path(argv[1], path_parts);
    node = kvfs_root_mount_dir;
    if (path_parts_count <= 1) {
        KPRINTF_ERROR("%s", "touch: invalid path");
        return OK_TRUE;
    }
    for (uint32_t i = 1; i < path_parts_count - 1; i++) {
        node = node->_ops->_lookup(node, path_parts[i]);
        if (node == NULL) {
            KPRINTF_ERROR("touch: no such file or directory called %s", path_parts[i]);
            return OK_TRUE;
        }
        if (node->_type != KVFS_DIR) {
            KPRINTF_ERROR("touch: not a directory %s", path_parts[i]);
            return OK_TRUE;
        }
    }
    tmp = node->_ops->_lookup(node, path_parts[path_parts_count - 1]);
    if (tmp != NULL) {
        kvfs_close(tmp);
        KPRINTF_ERROR("%s", "touch: file already exists");
        return OK_TRUE;
    }
    node->_ops->_create(node, path_parts[path_parts_count - 1]);
    return KO_FALSE;
}
