/*
** DELOS PROJECT, 2026
** include/kernel/fs/vfs/vfs_stat
** File description:
** VFS stat header file
*/

#include <kernel/sys/cred.h>
#include <types.h>

#ifndef KERNEL_FS_VFS_STAT_H_
    #define KERNEL_FS_VFS_STAT_H_

    #ifndef KVFS_STAT_MODE_MASK
        #define KVFS_STAT_MODE_MASK
        #define KVFS_STAT_IFMT   0170000
        #define KVFS_STAT_IFREG  0100000
        #define KVFS_STAT_IFDIR  0040000
        #define KVFS_STAT_IFLNK  0120000
        #define KVFS_STAT_IFCHR  0020000
        #define KVFS_STAT_IFBLK  0060000

        #define KVFS_STAT_TYPE(mode) ((mode) & KVFS_STAT_IFMT)
        #define KVFS_STAT_ISREG(mode) (KVFS_STAT_TYPE(mode) == KVFS_STAT_IFREG)
        #define KVFS_STAT_ISDIR(mode) (KVFS_STAT_TYPE(mode) == KVFS_STAT_IFDIR)
        #define KVFS_STAT_ISLNK(mode) (KVFS_STAT_TYPE(mode) == KVFS_STAT_IFLNK)
        #define KVFS_STAT_ISCHR(mode) (KVFS_STAT_TYPE(mode) == KVFS_STAT_IFCHR)
        #define KVFS_STAT_ISBLK(mode) (KVFS_STAT_TYPE(mode) == KVFS_STAT_IFBLK)
    #endif /* ifndef KVFS_STAT_MODE_MASK */

    #ifndef KVFS_STAT_PERM_MASK
        #define KVFS_STAT_PERM_MASK
        #define KVFS_STAT_IRUSR  0000400
        #define KVFS_STAT_IWUSR  0000200
        #define KVFS_STAT_IXUSR  0000100
        #define KVFS_STAT_CAN_USR_READ(mode)  ((mode) & KVFS_STAT_IRUSR)
        #define KVFS_STAT_CAN_USR_WRITE(mode) ((mode) & KVFS_STAT_IWUSR)
        #define KVFS_STAT_CAN_USR_EXEC(mode)  ((mode) & KVFS_STAT_IXUSR)

        #define KVFS_STAT_IRGRP  0000040
        #define KVFS_STAT_IWGRP  0000020
        #define KVFS_STAT_IXGRP  0000010
        #define KVFS_STAT_CAN_GRP_READ(mode)  ((mode) & KVFS_STAT_IRGRP)
        #define KVFS_STAT_CAN_GRP_WRITE(mode) ((mode) & KVFS_STAT_IWGRP)
        #define KVFS_STAT_CAN_GRP_EXEC(mode)  ((mode) & KVFS_STAT_IXGRP)

        #define KVFS_STAT_IROTH  0000004
        #define KVFS_STAT_IWOTH  0000002
        #define KVFS_STAT_IXOTH  0000001
        #define KVFS_STAT_CAN_OTH_READ(mode)  ((mode) & KVFS_STAT_IROTH)
        #define KVFS_STAT_CAN_OTH_WRITE(mode) ((mode) & KVFS_STAT_IWOTH)
        #define KVFS_STAT_CAN_OTH_EXEC(mode)  ((mode) & KVFS_STAT_IXOTH)
    #endif /* ifndef KVFS_STAT_PERM_MASK */

/*
 * @brief Structure for a stat entry.
 *        - mode = the type + permission integer using mask
 *        - nlink = number of links associated to this file
 *        - size = the file size in bytes
 *        - atime = the last access time
 *        - mtime = last modification time
 *        - ctime = last metadata modification time
 */
typedef struct vfs_stat_s {
    mode_t _mode;
    uint32_t _nlink;
    uint64_t _size;
    uint64_t _atime;
    uint64_t _mtime;
    uint64_t _ctime;
    uid_t _uid;
    gid_t _gid;
} vfs_stat_t;

/**
 * @brief Create an empty stat structure without any specific file related stuff.
 *
 * @param mode   The least value we need to have is its mode.
 *
 * @return The structure stat.
 */
vfs_stat_t
kvfs_stat_create(mode_t mode);

/**
 * @brief Update the access time to now.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_atime(vfs_stat_t *st);

/**
 * @brief Update the modification time to now + ctime modification.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_mtime(vfs_stat_t *st);

/**
 * @brief Update the change metadata time to now.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_update_ctime(vfs_stat_t *st);

/**
 * @brief Update the size of the stat buffer and modification time.
 *
 * @param st         The structure to change (pointer)
 * @param new_size   The new size :)
 */
void
kvfs_stat_update_size(vfs_stat_t *st, size_t new_size);

/**
 * @brief Change the mode of a file and update its ctime.
 *
 * @param st     The structure to change (pointer)
 * @param mode   The new mode
 */
void
kvfs_stat_chmod(vfs_stat_t *st, mode_t mode);

/**
 * @brief Increment the number of link of a stat buffer.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_inc_nlink(vfs_stat_t *st);

/**
 * @brief Decrement the number of link of a stat buffer.
 *
 * @param st     The structure to change (pointer)
 */
void
kvfs_stat_dec_nlink(vfs_stat_t *st);

/**
 * @brief Change to the value the number of link.
 *
 * @param st     The structure to change (pointer)
 * @param nlink  The number of links to have
 */
void
kvfs_stat_set_nlink(vfs_stat_t *st, size_t nlink);

/**
 * @brief Check if a user within a group can read or not a file.
 *
 * @param stat   The stat buffer pointer
 * @param cred   The cred buffer pointer
 *
 * @return OK_TRUE if can read, KO_FALSE otherwise.
 */
bool32_t
kvfs_stat_can_read(const vfs_stat_t *stat, const cred_t *cred);

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
kvfs_stat_can_write(const vfs_stat_t *stat, const cred_t *cred);

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
kvfs_stat_can_exec(const vfs_stat_t *stat, const cred_t *cred);

#endif /* ifndef KERNEL_FS_VFS_STAT_H_ */
