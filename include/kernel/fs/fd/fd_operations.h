/*
** DELOS PROJECT, 2026
** include/kernel/fs/fd/fd_operations
** File description:
** FD operations header file
*/

#include <kernel/fs/fd/fd.h>
#include <types.h>

#ifndef KERNEL_FS_FD_OPERATIONS_H_
    #define KERNEL_FS_FD_OPERATIONS_H_

/**
 * @brief Write some data in a file descriptor.
 *
 * @param fd       The file descriptor
 * @param buffer   The buffer to take the data from
 * @param len      Number of maximum byte to write
 *
 * @return Number of bytes written on the file.
 */
size_t
kfd_write(fd_t fd, const void *buffer, size_t len);

/**
 * @brief Read some data from a file descriptor.
 *
 * @param fd       The file descriptor
 * @param buffer   The buffer to put the data
 * @param len      Number of maximum byte to read
 *
 * @return Number of bytes read on the file.
 */
size_t
kfd_read(fd_t fd, void *buffer, size_t len);

/**
 * @brief Get metadata of a file descriptor using the stat structure.
 *
 * @param fd         The file descriptor to stat
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfd_stat(fd_t fd, vfs_stat_t *stat_ptr);

#endif /* ifndef KERNEL_FS_FD_OPERATIONS_H_ */
