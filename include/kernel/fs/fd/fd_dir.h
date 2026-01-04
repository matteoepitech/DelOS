/*
** DELOS PROJECT, 2026
** include/kernel/fs/fd/fd_DIR
** File description:
** FD DIR header file
*/

#include <kernel/fs/dirent.h>
#include <types.h>

#ifndef KERNEL_FS_FD_DIR_H_
    #define KERNEL_FS_FD_DIR_H_

/*
 * @brief Structure for directory. Got after an opendir().
 *        - fd    = the file descriptor of the directory opened
 */
typedef struct fd_dir_s {
    fd_t _fd;
} fd_dir_t;

/**
 * @brief Open a directory and get a structure which act like an iterator.
 *
 * @param path   The path to the directory to open
 *
 * @return The directory structure of the concerned path.
 */
fd_dir_t *
kfd_opendir(const char *path);

/**
 * @brief Close a directory iterator.
 *        Will free the node contained in and the structure itself.
 *
 * @param dir    The directory structure to close
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfd_closedir(fd_dir_t *dir);

/**
 * @brief Read one directory entry from a directory file descriptor.
 *
 * @param fd     File descriptor of an opened directory
 * @param out    Output directory entry
 *
 * @return OK_TRUE if an entry was read, KO_FALSE on EOF or error
 */
bool32_t
kfd_readdir(fd_t fd, dirent_t *out);

#endif /* ifndef KERNEL_FS_FD_DIR_H_ */
