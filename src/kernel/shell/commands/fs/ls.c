/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/ls
** File description:
** ls command source file
*/

#include <kernel/fs/fd/fd_dir.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
#include <kernel/fs/fd/fd.h>
#include <defines.h>

/**
 * @brief Command for ls.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_ls(uint32_t argc, char *argv[])
{
    dirent_t dirent = {0};
    fd_dir_t *dir = NULL;

    if (argc < 2) {
        dir = kfd_opendir(".");
    } else {
        dir = kfd_opendir(argv[1]);
    }
    if (dir == NULL) {
        KPRINTF_ERROR("ls: cannot open directory");
        return OK_TRUE;
    }
    while (kfd_readdir(dir->_fd, &dirent) == OK_TRUE) {
        KPRINTF_INFO("%s%s", dirent._name, dirent._type == KVFS_STAT_IFDIR ? "/" : "");
    }
    kfd_closedir(dir);
    return KO_FALSE;
}
