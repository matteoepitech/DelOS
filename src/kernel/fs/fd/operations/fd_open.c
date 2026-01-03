/*
** DELOS PROJECT, 2026
** src/kernel/fs/fd/operations/fd_open
** File description:
** FD open source file
*/

#include <kernel/fs/vfs/vfs_open.h>
#include <kernel/fs/fd/fd.h>

/**
 * @brief Open a file and go through its entire path to get the node associated to the end level.
 *
 * @param path   The complete path to a node (e.g. "/abc/dir/a.txt")
 * @param flags  The flags O_CREAT | O_RDONLY ...
 * @param mode   The mode (used when creating the file only)
 *
 * @return The file descriptor.
 */
fd_t
kfd_open(const char *path, int32_t flags, mode_t mode)
{
    vfs_node_t *node = kvfs_open(path, flags, mode);

    return kfd_create(node);
}
