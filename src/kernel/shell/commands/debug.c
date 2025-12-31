/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <utils/kstdlib/kstring.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/shell/shell.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <defines.h>

/**
 * @brief Command for debug.
 *
 * @param argc          The number of argument
 * @param argv[]        The array of argument
 *
 * @return The final code of the operation.
 */
uint8_t
kshell_debug(UNUSED uint32_t argc, UNUSED char *argv[])
{
    vfs_node_t *root = kvfs_mount("tmpfs", "/", NULL);
    if (root == NULL) {
        KPRINTF_ERROR("debug: failed to mount the tmpfs");
        return OK_TRUE;
    }
    ktmpfs_create_entry(root->_private, "file.txt", KTMPFS_FILE);

    KPRINTF_DEBUG("FS's name: %s", root->_fs->_name);
    KPRINTF_DEBUG("File type: %s", kvfs_get_type_string(root->_type));
    KPRINTF_DEBUG("File refcount: %d", root->_refcount);
    KPRINTF_DEBUG("File size: %d", root->_size);
    if (root->_private == NULL) {
        KPRINTF_ERROR("Private is null");
        return KO_FALSE;
    }
    KPRINTF_DEBUG("File name: %s", ((tmpfs_entry_t *) root->_private)->_name);

    vfs_node_t *file_node = kvfs_lookup(root, "file.txt");
    KPRINTF_DEBUG("FS's name: %s", file_node->_fs->_name);
    KPRINTF_DEBUG("File type: %s", kvfs_get_type_string(file_node->_type));
    KPRINTF_DEBUG("File refcount: %d", file_node->_refcount);
    KPRINTF_DEBUG("File size: %d", file_node->_size);
    if (file_node->_private == NULL) {
        KPRINTF_ERROR("Private is null");
        return KO_FALSE;
    }
    KPRINTF_DEBUG("File name: %s", ((tmpfs_entry_t *) file_node->_private)->_name);

    return KO_FALSE;
}
