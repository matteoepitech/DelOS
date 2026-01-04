/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/directory/fd_readdir
** File description:
** FD readdir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd_dir.h>
#include <utils/misc/print.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Read one directory entry from a directory file descriptor.
 *
 * @param fd     File descriptor of an opened directory
 * @param out    Output directory entry
 *
 * @return OK_TRUE if an entry was read, KO_FALSE on EOF or error
 */
bool32_t
kfd_readdir(fd_t fd, dirent_t *out)
{
    vfs_stat_t stat_buffer = {0};
    file_desc_t *desc = NULL;

    if (out == NULL) {
        return KO_FALSE;
    }
    desc = kfd_get(fd);
    if (desc == NULL || desc->_node == NULL) {
        return KO_FALSE;
    }
    if (kfd_check_access(fd, KFD_ACCESS_READ) == KO_FALSE) {
        return KO_FALSE;
    }
    if (kvfs_get_stat(desc->_node, &stat_buffer) == KO_FALSE) {
        return KO_FALSE;
    }
    if (KVFS_STAT_ISDIR(stat_buffer._mode) == KO_FALSE) {
        return KO_FALSE;
    }
    if (kvfs_readdir(desc->_node, &desc->_offset, out) == KO_FALSE) {
        return KO_FALSE;
    }
    return OK_TRUE;
}
