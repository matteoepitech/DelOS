/*
** DELOS PROJECT, 2025
** include/kernel/fs/fs
** File description:
** FS header file
*/

#include <types.h>

#ifndef KERNEL_FS_H_
    #define KERNEL_FS_H_

/**
 * @brief Init the file system stuff of the kernel.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kfs_init(void);

#endif /* ifndef KERNEL_FS_H_ */
