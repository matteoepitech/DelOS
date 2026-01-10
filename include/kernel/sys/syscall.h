/*
** DELOS PROJECT, 2026
** include/kernel/sys/syscall
** File description:
** SYSCALL header file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <types.h>

#ifndef KERNEL_SYS_SYSCALL_H_
    #define KERNEL_SYS_SYSCALL_H_

/**
 * @brief Syscall to change the current working directory.
 *        WARN: actually only supporting kvfs_cwd
 *
 * @param path   The path to change directory
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_chdir(const char *path);

/**
 * @brief Syscall to open a file descriptor.
 *
 * @param path   The path to open
 * @param flags  The flags to open the file with
 * @param mode   The mode to use when creating the file
 *
 * @return The file descriptor if worked, KFD_ERROR otherwise.
 */
fd_t
ksys_open(const char *path, int32_t flags, mode_t mode);

/**
 * @brief Syscall to close a file descriptor.
 *
 * @param fd   The file descriptor to close
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_close(fd_t fd);

/**
 * @brief Syscall to get the stat metadata of a file descriptor.
 *
 * @param fd         The file descriptor to stat
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_fstat(fd_t fd, vfs_stat_t *stat_ptr);

/**
 * @brief Syscall to get the stat metadata of a file descriptor.
 *
 * @param path       The path to the file
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_stat(const char *path, vfs_stat_t *stat_ptr);

/**
 * @brief Syscall to create a new directory at a specified path.
 *
 * @param path   The path to create the directory
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_mkdir(const char *path);

/**
 * @brief Syscall to unlink a file.
 *
 * @param path   The path to the file to unlink
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_unlink(const char *path);

/**
 * @brief Syscall to remove a directory using his path.
 *
 * @param path   The path to directory to remove
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_rmdir(const char *path);

#endif /* ifndef KERNEL_SYS_SYSCALL_H_ */
