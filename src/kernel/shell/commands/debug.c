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
    kvfs_mkdir(kvfs_root_mount_dir, "secret");
    vfs_node_t *secret_dir = kvfs_lookup(kvfs_root_mount_dir, "secret");
    kvfs_create(secret_dir, "secret.file");
    vfs_node_t *file = kvfs_open("/secret/secret.file");
    if (file == NULL) {
        KPRINTF_ERROR("debug: cannot opening secret.file");
        return OK_TRUE;
    }
    kvfs_close(file);
    kvfs_close(secret_dir);

    char buffer[] = "qdkjqx829N";
    vfs_node_t *a = kvfs_open("/secret/secret.file");
    kvfs_write(a, buffer, sizeof(buffer));
    kvfs_close(a);

    char content[1024] = {0};
    vfs_node_t *b = kvfs_open("/secret/secret.file");
    kvfs_read(b, content, sizeof(content));
    kvfs_close(b);
    KPRINTF_OK("%s", content);

    return KO_FALSE;
}
