/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_time
** File description:
** VFS stat time source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Update the access time to now.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_atime(vfs_stat_t *st)
{
    st->_atime = 0;// TODO: ktime_now()
}

/**
 * @brief Update the modification time to now + ctime modification.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_mtime(vfs_stat_t *st)
{
    st->_mtime = 0;// TODO: ktime_now()
    st->_ctime = 0;// TODO: ktime_now()
}

/**
 * @brief Update the change metadata time to now.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_ctime(vfs_stat_t *st)
{
    st->_ctime = 0;// TODO: ktime_now()
}
