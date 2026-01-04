/*
** DELOS PROJECT, 2026
** include/kernel/fs/vfs/vfs_open
** File description:
** VFS open header file
*/

#include <kernel/fs/vfs/vfs.h>
#include <types.h>

#ifndef KERNEL_FS_VFS_OPEN_H_
    #define KERNEL_FS_VFS_OPEN_H_

    #ifndef KVFS_O_PERMS
        #define KVFS_O_PERMS
        #define KVFS_O_ACCMODE  0x0003
        #define KVFS_O_RDONLY   0x0000
        #define KVFS_O_WRONLY   0x0001
        #define KVFS_O_RDWR     0x0002
    #endif /* ifndef KVFS_O_PERMS */

    #ifndef KVFS_O_MISC
        #define KVFS_O_MISC
        #define KVFS_O_CREAT    0x0040
        #define KVFS_O_EXCL     0x0080
        #define KVFS_O_TRUNC    0x0200
        #define KVFS_O_APPEND   0x0400 //TODO:
        #define KVFS_O_DIRECTORY 0x10000
    #endif /* ifndef KVFS_O_MISC */

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *        This version is returning NULL if the file doesn't exist.
 *        Use the API function kvfs_open() instead which can handle flags.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_lookup_open(const char *path);

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 * @param flags  The flags O_CREAT | O_RDONLY ...
 * @param mode   The mode (used when creating the file only)
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_open(const char *path, int32_t flags, mode_t mode);

/**
 * @brief Resolve and get the VFS node of a relative path using the start.
 *
 * @param start  The start of the resolving, NULL for root
 * @param path   The relative path to a node from the start (e.g. "abc/dir/a.txt")
 *
 * @return The VFS node of the path result. (Can be anything: file, dir, link, ...)
 */
vfs_node_t *
kvfs_resolve_from(vfs_node_t *start, const char *path);

/**
 * @brief Resolve the parent of a file using path.
 *
 * @param start      The start to check
 * @param path       The path to resolve
 * @param out_name   A buffer to stock the name of the final part on the path (used for creation e.g.)
 *
 * @return The node of the parent.
 */
vfs_node_t *
kvfs_resolve_parent_from(vfs_node_t *start, const char *path, char *out_name);

#endif /* ifndef KERNEL_FS_VFS_OPEN_H_ */
