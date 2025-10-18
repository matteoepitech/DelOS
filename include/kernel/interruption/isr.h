/*
** DELOS PROJECT, 2025
** include/kernel/interruption/isr
** File description:
** Interruption service routine header file
*/

#include "types.h"

#ifndef KERNEL_INTERRUTPION_ISR_H_
    #define KERNEL_INTERRUTPION_ISR_H_

/**
 * @brief Register an handler of a ISR in the isr_handlers variable.
 *
 * @param index                 The index in the IDT and isr_handlers
 * @param func_handler          The function to jump at
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kisr_register_handler(uint8_t index, void (*func_handler)(uint32_t, uint32_t));

/**
 * @brief Call the handler with the interruption number and his error code if provided.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided by the CPU
 */
void
kisr_handler(uint32_t int_no, uint32_t err_code);

#endif /* ifndef KERNEL_INTERRUTPION_ISR_H_ */
