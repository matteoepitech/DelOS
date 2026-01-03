/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_mode
** File description:
** VFS stat mode source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Change the mode of a file and update its ctime.
 *
 * @param st     The structure to change (pointer)
 * @param mode   The new mode
 */
void
kvfs_stat_chmod(vfs_stat_t *st, mode_t mode)
{
    st->_mode = (st->_mode & KVFS_STAT_IFMT) | mode;
    kvfs_stat_update_ctime(st);
}
