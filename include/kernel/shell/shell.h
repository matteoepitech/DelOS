/*
** EPITECH PROJECT, 2025
** include/kernel/shell/shell
** File description:
** Shell header file
*/

#include "types.h"

#ifndef KERNEL_SHELL_H_
    #define KERNEL_SHELL_H_

#define KERNEL_SHELL_BUFFER_SIZE 512

/**
 * @brief Start the shell and waiting for user prompt.
 *
 * @return OK_TRUE if worked KO_FALSE otherwise.
 */
bool32_t
kshell_start(void);

#endif /* ifndef KERNEL_SHELL_H_ */
