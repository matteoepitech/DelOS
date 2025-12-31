/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_write
** File description:
** TMPFS write source file
*/

#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Write data in the temporary virtual file system.
 *
 * @param node       The node of the file in the VFS
 * @param offset     The offset in the file
 * @param buffer     The buffer where the data to write is in
 * @param len        The number of bytes to write
 *
 * @return The size of the number of bytes write in the file.
 */
size_t
ktmpfs_write(vfs_node_t *node, off_t offset, const void *buffer, size_t len)
{

    return 0;
}
