/*
** DELOS PROJECT, 2026
** src/kernel/sys/syscall/sys_unlink
** File description:
** SYSCALL unlink source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <kernel/sys/syscall.h>
#include <defines.h>

/**
 * @brief Syscall to unlink a file.
 *
 * @param path   The path to the file to unlink
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_unlink(const char *path)
{
    if (path == NULL) {
        return -1;
    }
    if (kvfs_unlink(path) == KO_FALSE) {
        return -1;
    }
    return 0;
}
