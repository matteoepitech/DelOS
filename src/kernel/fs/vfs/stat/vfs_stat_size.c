/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_size
** File description:
** VFS stat size source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Update the size of the stat buffer and modification time.
 *
 * @param st         The structure to change (pointer)
 * @param new_size   The new size :)
 */
void
kvfs_stat_update_size(vfs_stat_t *st, size_t new_size)
{
    if (st->_size != new_size) {
        st->_size = new_size;
        kvfs_stat_update_mtime(st);
    }
}
