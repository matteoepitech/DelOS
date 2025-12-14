/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr_handler
** File description:
** Interruption service routine source file and for IRQs
*/

#include "kernel/interruption/idt.h"
#include "kernel/interruption/isr.h"
#include "kernel/misc/panic.h"
#include "kernel/tty/tty.h"
#include "defines.h"
#include "types.h"

/**
 * @brief Variable for the ISR functions pointer.
 *        This is an abstraction between the call ASM and C.
 *        The process is "int -> jump asm code -> jump isr_handler -> jump specific function".
 */
isr_handler_t isr_handlers[IDT_SIZE] = {0};

/**
 * @brief Register an handler of a ISR in the isr_handlers variable.
 *
 * @param index                 The index in the IDT and isr_handlers
 * @param func_handler          The function to jump at
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kisr_register_handler(uint8_t index, isr_handler_t func_handler)
{
    if (func_handler == NULL) {
        return KO_FALSE;
    }
    isr_handlers[index] = func_handler;
    return OK_TRUE;
}

/**
 * @brief Call the handler with the interruption number and his error code if provided.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided by the CPU
 */
void
kisr_handler(registers_t *regs)
{
    uint32_t int_no = regs->_int_no;

    if (regs == NULL) {
        KPANIC("Interruption's registers not pushed on stack.");
    } else if (isr_handlers[int_no] != NULL) {
        isr_handlers[int_no](regs);
    } else {
        KPANIC("Interruption not handled.");
    }
}
