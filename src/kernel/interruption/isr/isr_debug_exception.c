/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_debug_exception
** File description:
** ISR debug exception
*/

#include <kernel/interruption/isr.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>

/**
 * @brief ISR debug exception.
 *        We set here the eflags trap flag (bit 8) to 0 to continue the execution.
 *        Basically this debug exception can be called via lot of ways but the
 *        most common way is by doing a single step execution for debugging.
 *
 *        The process is, when you put the trap flag bit to 1 the CPU will
 *        make an interruption #DB for each instruction.
 *
 *        When you are on this interruption you can do your stuff but you want maybe
 *        to continue the execution of the program. To do so you will need to
 *        put the trap flag back to 0 to continue the execution.
 *
 * @param regs          The registers
 */
void
isr_debug_exception(registers_t *regs)
{
    KPRINTF_DEBUG("Debug step activated on an instruction.");
    DEACTIVATE_TRAP_FLAG(regs);
}
