/*
** DELOS PROJECT, 2025
** src/kernel/fs/tmpfs/tmpfs_read
** File description:
** TMPFS read source file
*/

#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <utils/misc/print.h>

/**
 * @brief Read data in the temporary virtual file system.
 *
 * @param node       The node of the file in the VFS
 * @param offset     The offset in the file
 * @param buffer     The buffer where to store the data read in (should be allocated to len size)
 * @param len        The number of byte to read
 *
 * @return The number of bytes read.
 */
size_t
ktmpfs_read(vfs_node_t *node, off_t offset, void *buffer, size_t len)
{
    KPRINTF_DEBUG("read from ktmpfs driver");
    return 0;
}
