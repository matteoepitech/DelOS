/*
** DELOS PROJECT, 2026
** include/kernel/fs/dirent
** File description:
** Dirent header file
*/

#include <types.h>

#ifndef KERNEL_FS_DIRENT_H_
    #define KERNEL_FS_DIRENT_H_

    #ifndef KFD_MAX_NAME_LEN
        #define KDIRENT_MAX_NAME_LEN 255
    #endif /* ifndef KFD_MAX_NAME_LEN */

/*
 * @brief Structure for re-implementation of the POSIX dirent structure.
 *        - inode = the identifier of the file
 *        - type  = the type of the file (provided from the stat buffer)
 *        - name  = the name of the file
 *
 *        This structure may changes in the future.
 */
typedef struct dirent_s {
    uint32_t _inode;
    uint32_t _type;
    char _name[KDIRENT_MAX_NAME_LEN];
} dirent_t;

#endif /* ifndef KERNEL_FS_DIRENT_H_ */
