/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/pwd
** File description:
** pwd command source file
*/

#include <kernel/fs/tmpfs/tmpfs.h>
#include <utils/kstdlib/kstring.h>
#include <utils/kstdlib/kmemory.h>
#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for pwd.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_pwd(UNUSED uint32_t argc, UNUSED char *argv[])
{
    char buffer[KVFS_MAX_PATH_PARTS * KVFS_MAX_NAME_LEN] = {0};
    vfs_node_t *tmp_node = NULL;
    uint32_t tmp_name_len = 0;
    char *tmp_name = NULL;

    tmp_node = kvfs_cwd;
    while (tmp_node != NULL) {
        tmp_name = ((tmpfs_entry_t *) tmp_node->_private)->_name;
        tmp_name_len = kstrlen(tmp_name);
        kmemmove(buffer, buffer + tmp_name_len, kstrlen(buffer));
        kmemcpy(buffer, tmp_name, tmp_name_len);
        tmp_node = tmp_node->_ops->_lookup(tmp_node, "..");
    }
    KPRINTF_INFO("%s", buffer);
    return KO_FALSE;
}
