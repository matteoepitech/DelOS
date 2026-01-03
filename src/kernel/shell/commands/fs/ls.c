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

    if (argc < 2) {
        dir = kvfs_opendir_from_node(kvfs_cwd);
    } else {
        dir = kvfs_opendir(argv[1]);
    }
    if (dir == NULL) {
        KPRINTF_ERROR("%s", "ls: cannot open directory");
        return OK_TRUE;
    }
    for (vfs_dirent_t *dirent = kvfs_readdir(dir); dirent != NULL; dirent = kvfs_readdir(dir)) {
        KPRINTF_INFO("%s%s", dirent->_name, KVFS_STAT_ISDIR(dirent->_type) == OK_TRUE ? "/" : "");
    }
    kvfs_closedir(dir);
    return KO_FALSE;
}
