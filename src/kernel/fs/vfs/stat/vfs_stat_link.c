/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_link
** File description:
** VFS stat link source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>

/**
 * @brief Increment the number of link of a stat buffer.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_inc_nlink(vfs_stat_t *st)
{
    st->_nlink++;
    kvfs_stat_update_ctime(st);
}

/**
 * @brief Decrement the number of link of a stat buffer.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_dec_nlink(vfs_stat_t *st)
{
    if (st->_nlink > 0)
        st->_nlink--;
    kvfs_stat_update_ctime(st);
}

/**
 * @brief Change to the value the number of link.
 *
 * @param st     The structure to change (pointer)
 * @param nlink  The number of links to have
 */
void
kvfs_stat_set_nlink(vfs_stat_t *st, size_t nlink)
{
    st->_nlink = nlink;
    kvfs_stat_update_ctime(st);
}
