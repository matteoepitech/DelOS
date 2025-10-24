/*
** DELOS PROJECT, 2025
** include/kernel/interruption/isr
** File description:
** Interruption service routine header file
*/

#include "types.h"

#ifndef KERNEL_INTERRUTPION_ISR_H_
    #define KERNEL_INTERRUTPION_ISR_H_

#ifndef ACTIVATE_TRAP_FLAG
    #define ACTIVATE_TRAP_FLAG(regs) regs->_eflags |= 0b100000000
#endif /* ifndef ACTIVATE_TRAP_FLAG */

#ifndef DEACTIVATE_TRAP_FLAG
    #define DEACTIVATE_TRAP_FLAG(regs) regs->_eflags &= ~0b100000000
#endif /* ifndef DEACTIVATE_TRAP_FLAG */

/**
 * @brief Register structure passed by the CPU when interruption.
 *        -...
 */
typedef struct registers_s {
    uint32_t _ds;
    uint32_t _es;
    uint32_t _edi;
    uint32_t _esi;
    uint32_t _ebp;
    uint32_t _esp;
    uint32_t _ebx;
    uint32_t _edx;
    uint32_t _ecx;
    uint32_t _eax;
    uint32_t _int_no;
    uint32_t _err_code;
    uint32_t _eip;
    uint32_t _cs;
    uint32_t _eflags;
    uint32_t _useresp;
    uint32_t _ss;
} registers_t;

/**
 * @brief Typedef for the handler isr function type.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided
 */
typedef void (*isr_handler_t)(registers_t *regs);

/**
 * @brief Register an handler of a ISR in the isr_handlers variable.
 *
 * @param index                 The index in the IDT and isr_handlers
 * @param func_handler          The function to jump at
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kisr_register_handler(uint8_t index, isr_handler_t func_handler);

/**
 * @brief Register an handler of a IRQ in the isr_handlers variable.
 *
 * @param index                 The index in the IDT and isr_handlers
 * @param func_handler          The function to jump at
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kirq_register_handler(uint8_t index, isr_handler_t func_handler);

/**
 * @brief Call the handler with the interruption number and his error code if provided.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided by the CPU
 */
void
kisr_handler(registers_t *regs);

#endif /* ifndef KERNEL_INTERRUTPION_ISR_H_ */
