/*
** DELOS PROJECT, 2026
** include/kernel/sys/syscall
** File description:
** SYSCALL header file
*/

#include <types.h>

#ifndef KERNEL_SYS_SYSCALL_H_
    #define KERNEL_SYS_SYSCALL_H_

/**
 * @brief Syscall to change the current working directory.
 *        WARN: actually only supporting kvfs_cwd
 *
 * @param path   The path to change directory
 *
 * @return O if worked, -1 if any error.
 */
int32_t
ksys_chdir(const char *path);

#endif /* ifndef KERNEL_SYS_SYSCALL_H_ */
