/*
** DELOS PROJECT, 2026
** include/kernel/fs/vfs/vfs_dir
** File description:
** VFS directory header file
*/

#include <kernel/fs/vfs/vfs.h>

#ifndef KERNEL_FS_VFS_DIR_H_
    #define KERNEL_FS_VFS_DIR_H_

/*
 * @brief Structure for a directory lookup. Only used for that reason.
 *        - dir_node = the directory VFS node
 *        - index    = the current lookup index (iterator way)
 */
typedef struct vfs_dir_s {
    vfs_node_t *_dir_node;
    uint32_t _index;
} vfs_dir_t;

/*
 * @brief Structure for re-implementation of the POSIX dirent structure.
 *        - inode = the identifier of the file
 *        - type  = the type of the file
 *        - name  = the name of the file
 *
 *        This structure may changes in the future.
 */
typedef struct vfs_dirent_s {
    uint32_t _inode;
    vfs_node_type_t _type;
    char _name[KVFS_MAX_NAME_LEN];
} vfs_dirent_t;

/**
 * @brief Open a directory and get a structure which act like an iterator.
 *
 * @param path   The path to the directory to open
 *
 * @return The directory structure of the concerned path.
 */
vfs_dir_t *
kvfs_opendir(const char *path);

/**
 * @brief Read one entry of a directory structure.
 *
 * @param dir    The directory structure (not a dirent)
 *
 * @return The structure of a directory entry.
 */
vfs_dirent_t *
kvfs_readdir(vfs_dir_t *dir);

/**
 * @brief Close a directory iterator.
 *        Will free the node contained in and the structure itself.
 *
 * @param dir    The directory structure to close
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kvfs_closedir(vfs_dir_t *dir);

#endif /* ifndef KERNEL_FS_VFS_DIR_H_ */
