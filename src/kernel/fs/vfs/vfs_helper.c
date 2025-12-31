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
