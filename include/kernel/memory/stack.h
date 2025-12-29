/*
** DELOS PROJECT, 2025
** include/kernel/memory/stack
** File description:
** Stack header file
*/

#include <types.h>

#ifndef KERNEL_MEMORY_STACK_H_
    #define KERNEL_MEMORY_STACK_H_

    #ifndef KSTACK_SIZE
        #define KSTACK_SIZE 8196 // WARN: Make sure to have the same value in the linker script associated to your architecture
    #endif /* ifndef KSTACK_SIZE */

/* @brief Variables from the linker script to get the start end end of the stack */
extern uint32_t __kernel_stack_start;
extern uint32_t __kernel_stack_end;

#endif /* ifndef KERNEL_MEMORY_STACK_H_ */
