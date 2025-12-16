/*
** DELOS PROJECT, 2025
** include/kernel/arch/i386/interruption/interruption
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
kinterruption_extern_stop(void);

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kinterruption_extern_start(void);

#endif /* ifndef KERNEL_INTERRUPTION_H_ */
