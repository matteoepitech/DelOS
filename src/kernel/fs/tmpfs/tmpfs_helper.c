/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_helper
** File description:
** TMPFS helper source file
*/

#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>

/* @brief Variable containing a static version of all operations of TMPFS fs */
vfs_ops_t ktmpfs_operations = {
    ktmpfs_read,
    ktmpfs_write,
    ktmpfs_lookup
};

/**
 * @brief Get the structure containing every callback for that filesystem.
 *
 * @return Pointer to the vfs_ops_t structure for the TMPFS fs.
 */
vfs_ops_t *
ktmpfs_get_operations(void)
{
    return &ktmpfs_operations;
}
