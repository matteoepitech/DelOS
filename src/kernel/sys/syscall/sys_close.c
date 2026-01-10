/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_close
** File description:
** SYSCALL close source file
*/

#include <kernel/fs/fd/fd.h>
#include <kernel/sys/syscall.h>
#include <defines.h>

/**
 * @brief Syscall to close a file descriptor.
 *
 * @param fd   The file descriptor to close
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_close(fd_t fd)
{
    if (kfd_close(fd) == KO_FALSE) {
        return -1;
    }
    return 0;
}
