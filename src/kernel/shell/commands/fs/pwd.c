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
    vfs_node_t *node = kvfs_lookup(kvfs_cwd, ".");
    vfs_node_t *parent = NULL;
    const char *name = NULL;
    uint32_t name_len = 0;
    uint32_t buf_len = 0;

    if (node == NULL) {
        KPRINTF_ERROR("%s", "pwd: failed to resolve current directory");
        return OK_TRUE;
    }
    while (node != NULL) {
        kvfs_lookup(node, "..");
        if (parent == NULL || parent->_private == node->_private) {
            kvfs_close(parent);
            break;
        }
        name = ((tmpfs_entry_t *) node->_private)->_name;
        name_len = kstrlen(name);
        kmemmove(buffer + name_len + 1, buffer, buf_len + 1);
        buffer[0] = '/';
        kmemcpy(buffer + 1, name, name_len);
        buf_len += name_len + 1;
        kvfs_close(node);
        node = parent;
    }
    kvfs_close(node);
    if (buffer[0] == '\0') {
        buffer[0] = '/';
        buffer[1] = '\0';
    }
    KPRINTF_INFO("%s", buffer);
    return KO_FALSE;
}
