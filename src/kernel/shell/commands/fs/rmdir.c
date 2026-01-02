/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/fs/rmdir
** File description:
** rmdir command source file
*/

#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for rmdir.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_rmdir(uint32_t argc, char *argv[])
{
    if (argc < 2) {
        KPRINTF_ERROR("%s", "usage: rmdir <path>");
        return OK_TRUE;
    }
    kvfs_rmdir(argv[1]);
    return KO_FALSE;
}
