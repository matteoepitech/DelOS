/*
** DELOS PROJECT, 2025
** src/kernel/shell/commands/misc/debug
** File description:
** debug command source file
*/

#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/memory/api/kmalloc.h>
#include <kernel/fs/vfs/vfs_dir.h>
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
    // ------- SETUP -------
    kvfs_mkdir(kvfs_root_mount_dir, "secret");
    vfs_node_t *secret_dir = kvfs_lookup(kvfs_root_mount_dir, "secret");
    kvfs_create(secret_dir, "secret.file");
    kvfs_create(secret_dir, "hayo");
    kvfs_create(secret_dir, "aaaa");
    kvfs_mkdir(secret_dir, "home");
    // ----- END SETUP -----

    vfs_dir_t *dir = kvfs_opendir("/secret/");
    if (dir == NULL) {
        KPRINTF_ERROR("debug: cannot open the directory");
        return OK_TRUE;
    }
    vfs_dirent_t *dirent = kvfs_readdir(dir);
    while (dirent != NULL) {
        if (dirent->_type == KVFS_DIR) {
            KPRINTF_DEBUG("%s/", dirent->_name);
        } else {
            KPRINTF_DEBUG("%s", dirent->_name);
        }
        dirent = kvfs_readdir(dir);
    }
    kvfs_closedir(dir);
    return KO_FALSE;
}
