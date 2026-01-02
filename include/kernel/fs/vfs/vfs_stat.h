/*
** DELOS PROJECT, 2026
** include/kernel/fs/vfs/vfs_stat
** File description:
** VFS stat header file
*/

#include <types.h>

#ifndef KERNEL_FS_VFS_STAT_H_
    #define KERNEL_FS_VFS_STAT_H_

    #ifndef KVFS_STAT_MODE_MASK    
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
        #define KVFS_STAT_IRUSR  0000400
        #define KVFS_STAT_IWUSR  0000200
        #define KVFS_STAT_IXUSR  0000100

        #define KVFS_STAT_CAN_READ(mode)  ((mode) & KVFS_STAT_IRUSR)
        #define KVFS_STAT_CAN_WRITE(mode) ((mode) & KVFS_STAT_IWUSR)
        #define KVFS_STAT_CAN_EXEC(mode)  ((mode) & KVFS_STAT_IXUSR)
    #endif /* ifndef KVFS_STAT_PERM_MASK */

/**
 * @brief Mode typedef unsigned integer 32 bits.
 */
typedef uint32_t mode_t;

/*
 * @brief Structure for a stat entry.
 *        - mode = the type + permission integer using mask
 *        - nlink = number of links associated to this file
 *        - size = the file size in bytes
 *        - atime = the last access time
 *        - mtime = last metadata modification time
 *        - ctime = last modification time
 */
typedef struct vfs_stat_s {
    mode_t _mode;
    uint32_t _nlink;
    uint64_t _size;
    uint64_t _atime;
    uint64_t _mtime;
    uint64_t _ctime;
} vfs_stat_t;

#endif /* ifndef KERNEL_FS_VFS_STAT_H_ */
