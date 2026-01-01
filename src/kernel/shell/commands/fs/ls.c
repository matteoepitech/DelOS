/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/ls
** File description:
** ls command source file
*/

#include <kernel/fs/vfs/vfs_dir.h>
#include <kernel/shell/shell.h>
#include <utils/misc/print.h>
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
    vfs_dir_t *dir = NULL;
    char *path = "/";

    if (argc >= 2) {
        if (kvfs_is_absolute_path(argv[1]) == KO_FALSE) {
            KPRINTF_ERROR("ls: only absolute path is supported yet");
            return OK_TRUE;
        }
        path = argv[1];
    }
    dir = kvfs_opendir(path);
    if (dir == NULL) {
        KPRINTF_ERROR("ls: cannot open directory %s", path);
        return OK_TRUE;
    }
    for (vfs_dirent_t *dirent = kvfs_readdir(dir); dirent != NULL; dirent = kvfs_readdir(dir)) {
        KPRINTF_INFO("%s%s", dirent->_name, dirent->_type == KVFS_DIR ? "/" : "");
    }
    kvfs_closedir(dir);
    return KO_FALSE;
}
