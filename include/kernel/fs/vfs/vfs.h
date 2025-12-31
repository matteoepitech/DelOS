/*
** DELOS PROJECT, 2025
** include/kernel/fs/vfs
** File description:
** VFS header file
*/

#include <defines.h>
#include <types.h>

#ifndef KERNEL_FS_VFS_H_
    #define KERNEL_FS_VFS_H_

    #ifndef KVFS_TYPE_MAX_LEN
        #define KVFS_TYPE_MAX_LEN 8
    #endif /* ifndef KVFS_TYPE_MAX_LEN */

    #ifndef KVFS_MOUNT_PATH_MAX_LEN
        #define KVFS_MOUNT_PATH_MAX_LEN 64 
    #endif /* ifndef KVFS_MOUNT_PATH_MAX_LEN */

    #ifndef KVFS_REGISTRY_LEN
        #define KVFS_REGISTRY_LEN 1
    #endif /* ifndef KVFS_REGISTRY_LEN */

/*
 * @brief This enumeration contains all differents type of a node for the VFS.
 */
typedef enum {
    KVFS_FILE,
    KVFS_DIR,
    KVFS_SYMLINK,
    KVFS_DEVICE
} vfs_node_type_t;

/*
 * @brief Structure for a VFS node which is a file object in memory for file, dir, link, ...
 *        - type     = the type of the node (file, dir, symlink, device)
 *        - size     = the size in bytes of the file
 *        - refcount = the number of reference for a file before closing or deleting it (depends on case usage)
 *        - ops      = the function pointers (callback) for the differents actions of the specified fs
 *        - fs       = pointer to the fs driver used by this node (not an instance)
 *        - private  = the pointer to something we don't know (used by the fs drivers)
 */
typedef struct vfs_node_s {
    vfs_node_type_t _type;
    uint32_t _size;
    uint32_t _refcount;
    struct vfs_ops_s *_ops;
    struct vfs_fs_s *_fs;
    void *_private;
} vfs_node_t;

/*
 * @brief Structure for a VFS file system.
 *        - name  = the name of the filesystem in a string "ext2", "tar", "fat32"
 *        - mount = the function pointer to the mount callback
 */
typedef struct vfs_fs_s {
    const char _name[KVFS_TYPE_MAX_LEN];
    vfs_node_t *(*_mount)(void *device);
} vfs_fs_t;

/*
 * @brief Structure for a VFS mount of a file system.
 *        - mount_location = the location in a string of where the fs is mounted
 *        - fs             = pointer to the fs driver used by this mount (not an instance)
 *        - root           = the node of the root directory/file of that fs
 */
typedef struct vfs_mount_s {
    char _mount_location[KVFS_MOUNT_PATH_MAX_LEN];
    vfs_fs_t *_fs;
    vfs_node_t *_root;
} vfs_mount_t;

/*
 * @brief Structure for all VFS operations like open, read, write.
 *        This is using for callback implementations for differentes file system.
 *        - read   = the function pointer to read data from the node
 *        - write  = the function pointer to write data from the node
 *        - lookup = the function pointer to get another node from a node
 */
typedef struct vfs_ops_s {
    size_t (*_read)(vfs_node_t *node, off_t offset, void *buffer, size_t len);
    size_t (*_write)(vfs_node_t *node, off_t offset, const void *buffer, size_t len);
    vfs_node_t *(*_lookup)(vfs_node_t *node, const char *next_level);
} vfs_ops_t;

#endif /* ifndef KERNEL_FS_VFS_H_ */
