/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/operations/fd_stat
** File description:
** FD stat source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Get metadata of a file descriptor using the stat structure.
 *
 * @param fd         The file descriptor to stat
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfd_stat(fd_t fd, vfs_stat_t *stat_ptr)
{
    file_desc_t *fd_struct = kfd_get(fd);

    if (fd_struct == NULL || stat_ptr == NULL || fd_struct->_node == NULL) {
        return KO_FALSE;
    }
    return kvfs_stat_from_node(fd_struct->_node, stat_ptr);
}
