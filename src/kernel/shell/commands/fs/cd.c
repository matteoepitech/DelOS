/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/cd
** File description:
** cd command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for cd.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_cd(uint32_t argc, char *argv[])
{
    vfs_node_t *dir_to_cd = NULL;

    if (argc < 2) {
        kvfs_close(kvfs_cwd);
        kvfs_cwd = kvfs_open("/");
        return KO_FALSE;
    }
    dir_to_cd = kvfs_open(argv[1]);
    if (dir_to_cd == NULL) {
        KPRINTF_ERROR("cd: failed to change directory");
        return OK_TRUE;
    }
    kvfs_close(kvfs_cwd);
    kvfs_cwd = dir_to_cd;
    return KO_FALSE;
}
