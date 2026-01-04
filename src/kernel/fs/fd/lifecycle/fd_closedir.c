/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/directory/fd_closedir
** File description:
** FD closedir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd_dir.h>
#include <utils/misc/print.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Close a directory iterator.
 *        Will free the node contained in and the structure itself.
 *
 * @param dir    The directory structure to close
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfd_closedir(fd_dir_t *dir)
{
    if (dir == NULL) {
        return KO_FALSE;
    }
    if (kfd_close(dir->_fd) == KO_FALSE) {
        return KO_FALSE;
    }
    kfree(dir);
    return OK_TRUE;
}
