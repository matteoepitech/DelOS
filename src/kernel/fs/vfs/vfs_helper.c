/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_helper
** File description:
** VFS helper source file
*/

#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Give us the pointer to the literal string of a type node name.
 *
 * @param type   The type of the node we want to get the string from
 *
 * @return The pointer to the literal string 
 */
char *
kvfs_get_type_string(vfs_node_type_t type)
{
    switch (type) {
        case KVFS_DIR:
            return "directory";
        case KVFS_FILE:
            return "file";
        case KVFS_SYMLINK:
            return "symbolic link";
        case KVFS_DEVICE:
            return "device file";
        default:
            return "unknown type";
    }
    return NULL;
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
    size_t j = 0;

    if (!path || KVFS_MAX_PATH_PARTS == 0) {
        return 0;
    }
    if (path[0] == '/') {
        if (count >= KVFS_MAX_PATH_PARTS) {
            return count;
        }
        tokens[count][0] = '/';
        tokens[count][1] = '\0';
        count++;
        i = 1;
    }
    while (path[i] != '\0' && count < KVFS_MAX_PATH_PARTS) {
        for (; path[i] == '/'; i++);
        if (path[i] == '\0') {
            break;
        }
        j = 0;
        while (path[i] != '/' && path[i] != '\0' && j < KVFS_MAX_NAME_LEN - 1) {
            tokens[count][j] = path[i];
            j++;
            i++;
        }
        tokens[count][j] = '\0';
        count++;
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
