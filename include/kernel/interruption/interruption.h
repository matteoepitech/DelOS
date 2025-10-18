/*
** EPITECH PROJECT, 2025
** include/kernel/interruption/interruption
** File description:
** Interruption header file
*/

#ifndef KERNEL_INTERRUPTION_H_
    #define KERNEL_INTERRUPTION_H_

/**
 * @brief Stop the interruptions by clearing the interruption flag.
 *        cli -> clear interruption flag
 */
void
kstop_interruption(void);

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 */
void
kstart_interruption(void);

#endif /* ifndef KERNEL_INTERRUPTION_H_ */
