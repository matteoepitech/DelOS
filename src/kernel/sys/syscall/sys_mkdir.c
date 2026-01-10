/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_mkdir
** File description:
** SYSCALL mkdir source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/sys/syscall.h>
#include <kernel/fs/fd/fd.h>

/**
 * @brief Syscall to create a new directory at a specified path.
 *
 * @param path   The path to create the directory
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_mkdir(const char *path)
{
    fd_t dir = KFD_ERROR;

    if (kstrcmp(path, "..") == 0 || kstrcmp(path, ".") == 0 || kstrcmp(path, "/") == 0) {
        return -1;
    }
    dir = kfd_open(path, KVFS_O_CREAT | KVFS_O_DIRECTORY | KVFS_O_EXCL, 0666);
    if (dir != KFD_ERROR) {
        kfd_close(dir);
        return 0;
    }
    return -1;
}
