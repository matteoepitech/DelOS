/*
** DELOS PROJECT, 2025
** src/kernel/fs/vfs/vfs_mount
** File description:
** VFS mount source file
*/

#include <kernel/fs/vfs/vfs_registry.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Mount a filesystem in our VFS architecture.
 *
 * @param fs_name    The name of the file system (need to be exact)
 * @param location   Where to locate that mounting
 * @param device     The device pointer on how to access data
 *
 * @return The VFS node of the root of that mounting.
 */
vfs_node_t *
kvfs_mount(const char *fs_name, const char *location, void *device)
{
    vfs_fs_t *fs = NULL;

    if (fs_name == NULL || location == NULL) {
        return NULL;
    }
    fs = kvfs_get_fs(fs_name);
    if (fs == NULL) {
        return NULL;
    }
    return fs->_mount(location, device);
}
