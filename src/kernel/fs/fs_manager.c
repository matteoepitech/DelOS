/*
** DELOS PROJECT, 2025
** src/kernel/fs/fs_manager
** File description:
** FS manager source file
*/

#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>
#include <kernel/fs/fs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Init the file system stuff of the kernel.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfs_init(void)
{
    vfs_node_t *root = kvfs_mount("tmpfs", "/", NULL);

    if (root == NULL) {
        KPRINTF_ERROR("file_system: failed to mount the tmpfs");
        return KO_FALSE;
    }
    kvfs_cwd = root;
    KPRINTF_OK("file_system: successfully mounted the kernel's tmpfs");
    return OK_TRUE;
}
