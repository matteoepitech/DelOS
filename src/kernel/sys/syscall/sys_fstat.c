/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_fstat
** File description:
** SYSCALL fstat source file
*/

#include <kernel/fs/fd/fd_operations.h>
#include <kernel/sys/syscall.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Syscall to get the stat metadata of a file descriptor.
 *
 * @param fd         The file descriptor to stat
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_fstat(fd_t fd, vfs_stat_t *stat_ptr)
{
    if (kfd_stat(fd, stat_ptr) == KO_FALSE) {
        return -1;
    }
    return 0;
}
