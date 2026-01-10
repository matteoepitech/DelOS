/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_stat
** File description:
** SYSCALL stat source file
*/

#include <kernel/fs/fd/fd_operations.h>
#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/sys/syscall.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Syscall to get the stat metadata of a file descriptor.
 *
 * @param path       The path to the file
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_stat(const char *path, vfs_stat_t *stat_ptr)
{
    fd_t fd = KFD_ERROR;

    if (path == NULL || stat_ptr == NULL) {
        return -1;
    }
    fd = kfd_open(path, KVFS_O_RDONLY, 0);
    if (fd == -1) {
        return -1;
    }
    if (kfd_stat(fd, stat_ptr) == KO_FALSE) {
        return -1;
    }
    return 0;
}
