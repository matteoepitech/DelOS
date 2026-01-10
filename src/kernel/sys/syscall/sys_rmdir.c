/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_rmdir
** File description:
** SYSCALL rmdir source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/sys/syscall.h>
#include <kernel/fs/fd/fd.h>

/**
 * @brief Syscall to remove a directory using his path.
 *
 * @param path   The path to directory to remove
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_rmdir(const char *path)
{
    bool32_t rmdir_r = KO_FALSE;

    if (kstrcmp(path, "..") == 0 || kstrcmp(path, ".") == 0 || kstrcmp(path, "/") == 0) {
        return -1;
    }
    rmdir_r = kvfs_rmdir(path);
    if (rmdir_r == KO_FALSE) {
        return -1;
    }
    return 0;
}
