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
    vfs_node_t *file = NULL;

    kvfs_create(kvfs_root_mount_dir, "file.txt");
    kvfs_mkdir(kvfs_root_mount_dir, "secret");
    vfs_node_t *secret_dir = kvfs_lookup(kvfs_root_mount_dir, "secret");
    kvfs_create(secret_dir, "secret.file");
    file = kvfs_open("/file.txt");
    if (file == NULL) {
        KPRINTF_ERROR("debug: cannot opening file.txt");
        return OK_TRUE;
    }
    kvfs_close(file);
    file = kvfs_open("/secret/secret.file");
    if (file == NULL) {
        KPRINTF_ERROR("debug: cannot opening secret.file");
        return OK_TRUE;
    }
    kvfs_close(file);
    kvfs_close(secret_dir);
    return KO_FALSE;
}
