/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_breakpoint
** File description:
** ISR breakpoint
*/

#include <kernel/interruption/isr.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief ISR breapoint.
 *
 * @param regs          The registers
 */
void
isr_breakpoint(UNUSED isr_registers_t *regs)
{
    KPRINTF_DEBUG("A breakpoint has been triggered.");
}
