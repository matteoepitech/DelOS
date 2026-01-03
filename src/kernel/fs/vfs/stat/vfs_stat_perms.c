/*
** DELOS PROJECT, 2026
** src/kernel/fs/vfs/stat/vfs_stat_perms
** File description:
** VFS perms source file
*/

#include <kernel/fs/vfs/vfs_stat.h>
#include <kernel/fs/vfs/vfs.h>
#include <defines.h>
#include <types.h>

/**
 * @brief Check if a user within a group can read or not a file.
 *        Bypassing root user (0).
 *
 * @param stat   The stat buffer pointer
 * @param cred   The cred buffer pointer
 *
 * @return OK_TRUE if can read, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat_can_read(const vfs_stat_t *stat, const cred_t *cred)
{
    if (stat == NULL || cred == NULL) {
        return KO_FALSE;
    }
    if (cred->_uid == 0) {
        return OK_TRUE;
    }
    if (stat->_uid == cred->_uid && KVFS_STAT_CAN_USR_READ(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    if (stat->_gid == cred->_gid && KVFS_STAT_CAN_GRP_READ(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    return KVFS_STAT_CAN_OTH_READ(stat->_mode);
}

/**
 * @brief Check if a user within a group can write or not a file.
 *        Bypassing root user (0).
 *
 * @param stat   The stat buffer pointer
 * @param cred   The cred buffer pointer
 *
 * @return OK_TRUE if can write, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat_can_write(const vfs_stat_t *stat, const cred_t *cred)
{
    if (stat == NULL || cred == NULL) {
        return KO_FALSE;
    }
    if (cred->_uid == 0) {
        return OK_TRUE;
    }
    if (stat->_uid == cred->_uid && KVFS_STAT_CAN_USR_WRITE(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    if (stat->_gid == cred->_gid && KVFS_STAT_CAN_GRP_WRITE(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    return KVFS_STAT_CAN_OTH_WRITE(stat->_mode);
}

/**
 * @brief Check if a user within a group can exec or not a file.
 *        Bypassing root user (0).
 *
 * @param stat   The stat buffer pointer
 * @param cred   The cred buffer pointer
 *
 * @return OK_TRUE if can exec, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat_can_exec(const vfs_stat_t *stat, const cred_t *cred)
{
    if (stat == NULL || cred == NULL) {
        return KO_FALSE;
    }
    if (cred->_uid == 0) {
        return OK_TRUE;
    }
    if (stat->_uid == cred->_uid && KVFS_STAT_CAN_USR_EXEC(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    if (stat->_gid == cred->_gid && KVFS_STAT_CAN_GRP_EXEC(stat->_mode) != KO_FALSE) {
        return OK_TRUE;
    }
    return KVFS_STAT_CAN_OTH_EXEC(stat->_mode);
}
