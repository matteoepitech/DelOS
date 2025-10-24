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
 *        This only manage the external interruptions like IRQs.
 */
void
kstop_interruption_extern(void);

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kstart_interruption_extern(void);

#endif /* ifndef KERNEL_INTERRUPTION_H_ */
