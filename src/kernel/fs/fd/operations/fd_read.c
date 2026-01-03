/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/operations/fd_read
** File description:
** FD read source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

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
kfd_read(fd_t fd, void *buffer, size_t len)
{
    file_desc_t *fd_struct = NULL;
    const cred_t cred = {0, 0};
    size_t read_bytes = 0;
    vfs_stat_t st = {0};

    if (buffer == NULL || len == 0) {
        return 0;
    }
    fd_struct = kfd_get(fd);
    if (fd_struct == NULL || fd_struct->_node == NULL) {
        return 0;
    }
    if ((fd_struct->_flags & KVFS_O_ACCMODE) == KVFS_O_WRONLY) {
        return 0;
    }
    if (kvfs_get_stat(fd_struct->_node, &st) == KO_FALSE) {
        return 0;
    }
    if (kvfs_stat_can_read(&st, &cred) == KO_FALSE) {
        return 0;
    }
    read_bytes = kvfs_read(fd_struct->_node, fd_struct->_offset, buffer, len);
    if (read_bytes > 0) {
        fd_struct->_offset += read_bytes;
    }
    return read_bytes;
}
