/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/operations/fd_close
** File description:
** FD close source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Close a file descriptor and drop its reference to the VFS node.
 *
 * @param fd   The file descriptor to close
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfd_close(fd_t fd)
{
    file_desc_t *fd_struct = kfd_get(fd);

    if (fd_struct == NULL) {
        return KO_FALSE;
    }
    if (fd_struct->_refcount > 1) {
        fd_struct->_refcount--;
        return OK_TRUE;
    }
    kvfs_close(fd_struct->_node);
    kfree(fd_struct);
    kfd_table[fd] = NULL;
    return OK_TRUE;
}
