/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_open
** File description:
** SYSCALL open source file
*/

#include <kernel/fs/fd/fd.h>
#include <kernel/sys/syscall.h>

/**
 * @brief Syscall to open a file descriptor.
 *
 * @param path   The path to open
 * @param flags  The flags to open the file with
 * @param mode   The mode to use when creating the file
 *
 * @return The file descriptor if worked, KFD_ERROR otherwise.
 */
fd_t
ksys_open(const char *path, int32_t flags, mode_t mode)
{
    if (path == NULL) {
        return KFD_ERROR;
    }
    return kfd_open(path, flags, mode);
}
