/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_debug_exception
** File description:
** ISR debug exception
*/

#include "kernel/interruption/isr.h"
#include "kernel/tty/tty.h"

/**
 * @brief ISR debug exception.
 *        We set here the eflags trap flag (bit 8) to 0 to continue the execution.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided
 */
void
isr_debug_exception(registers_t *regs)
{
    KDEBUG_TTY("Debug exception.");
    regs->_eflags &= ~0x100;
}
