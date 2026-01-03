/*
** DELOS PROJECT, 2026
** src/kernel/fs/tmpfs/operations/tmpfs_readdir
** File description:
** TMPFS readdir source file
*/

#include <utils/kstdlib/kstring.h>
#include <kernel/fs/vfs/vfs_dir.h>
#include <kernel/fs/tmpfs/tmpfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Fill informations about the res into dirent.
 *
 * @param dirent     The structure to fill out
 * @param res        The final child we got
 *
 * @return OK_TRUE if worked, KO_FALSE othewise.
 */
static bool32_t
fill_out_dirent(vfs_dirent_t *dirent, tmpfs_entry_t *res)
{
    if (res == NULL) {
        return KO_FALSE;
    }
    dirent->_inode = 0; // NOT USED on TMPFS
    kstrcpy(dirent->_name, res->_name);
    dirent->_type = KVFS_STAT_TYPE(res->_stat._mode);
    return OK_TRUE;
}

/**
 * @brief Iterate through the VFS node directory.
 *
 * @param dir        The directory strcuture (VFS node)
 * @param index      The current index in the directory (iterator way)
 * @param dirent     A pointer to the structure to fill out of informations
 *
 * @return OK_TRUE if worked, KO_FALSE othewise.
 */
bool32_t
ktmpfs_readdir(vfs_node_t *dir, uint32_t index, vfs_dirent_t *dirent)
{
    tmpfs_entry_t *dir_entry = NULL;
    tmpfs_entry_t *child = NULL;

    if (dir == NULL || dirent == NULL) {
        return KO_FALSE;
    }
    dir_entry = (tmpfs_entry_t *) dir->_private;
    child = dir_entry->_dir._child;
    kvfs_stat_update_atime(&dir_entry->_stat);
    for (; index > 0; index--) {
        if (child == NULL) {
            break;
        }
        child = child->_next;
    }
    return fill_out_dirent(dirent, child);
}
