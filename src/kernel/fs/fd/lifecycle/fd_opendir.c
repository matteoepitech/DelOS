/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/directory/fd_opendir
** File description:
** FD opendir source file
*/

#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd_dir.h>
#include <utils/misc/print.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Open a directory and get a structure which act like an iterator.
 *
 * @param path   The path to the directory to open
 *
 * @return The directory structure of the concerned path.
 */
fd_dir_t *
kfd_opendir(const char *path)
{
    fd_dir_t *dir = NULL;

    if (path == NULL) {
        return NULL;
    }
    dir = kmalloc(sizeof(fd_dir_t));
    dir->_fd = kfd_open(path, KVFS_O_RDONLY | KVFS_O_DIRECTORY, 0);
    if (dir->_fd == KFD_ERROR) {
        kfree(dir);
        return NULL;
    }
    return dir;
}
