/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/cd
** File description:
** cd command source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/sys/syscall.h>
#include <kernel/shell/shell.h>
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
    if (argc < 2) {
        return ksys_chdir("/") == -1 ? KO_FALSE : OK_TRUE;
    } else {
        return ksys_chdir(argv[1]) == -1 ? KO_FALSE : OK_TRUE;
    }
}
