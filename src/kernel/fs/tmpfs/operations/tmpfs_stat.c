/*
** DELOS PROJECT, 2026
** src/kernel/fs/tmpfs/operations/tmpfs_stat
** File description:
** TMPFS stat source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Copy the data stat of source into stat_ptr.
 *
 * @param stat_ptr   Where to copy the stat data to
 * @param source     Where to take data from
 */
static void
fill_stat_ptr(vfs_stat_t *stat_ptr, vfs_stat_t *source)
{
    stat_ptr->_atime = source->_atime;
    stat_ptr->_ctime = source->_ctime;
    stat_ptr->_mtime = source->_mtime;
    stat_ptr->_mode  = source->_mode;
    stat_ptr->_nlink = source->_nlink;
    stat_ptr->_size  = source->_size;
}

/**
 * @brief Get metadata using the stat structure of a file or directory or such.
 *
 * @param node       The node of the file to get stat from
 * @param stat_ptr   The pointer to the stat buffer
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
ktmpfs_stat(vfs_node_t *node, vfs_stat_t *stat_ptr)
{
    tmpfs_entry_t *entry = NULL;

    if (node == NULL || stat_ptr == NULL) {
        return KO_FALSE;
    }
    entry = node->_private;
    fill_stat_ptr(stat_ptr, &entry->_stat);
    return OK_TRUE;
}
