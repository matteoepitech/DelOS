/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/operations/fd_write
** File description:
** FD write source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

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
kfd_write(fd_t fd, const void *buffer, size_t len)
{
    file_desc_t *fd_struct = NULL;
    const cred_t cred = {0, 0};
    vfs_stat_t st = {0};
    size_t written = 0;

    if (buffer == NULL || len == 0) {
        return 0;
    }
    fd_struct = kfd_get(fd);
    if (fd_struct == NULL || fd_struct->_node == NULL) {
        return 0;
    }
    if (kfd_check_access(fd, KFD_ACCESS_WRITE) == KO_FALSE) {
        return 0;
    }
    if (kvfs_get_stat(fd_struct->_node, &st) == KO_FALSE) {
        return 0;
    }
    if (kvfs_stat_can_write(&st, &cred) == KO_FALSE) {
        return 0;
    }
    if (fd_struct->_node->_ops == NULL || fd_struct->_node->_ops->_write == NULL) {
        return 0;
    }
    written = kvfs_write(fd_struct->_node, &fd_struct->_offset, buffer, len);
    return written;
}
