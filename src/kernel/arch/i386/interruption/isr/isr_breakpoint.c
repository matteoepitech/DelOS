/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/isr/isr_breakpoint
** File description:
** ISR breakpoint
*/

#include <kernel/arch/i386/interruption/isr.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief ISR breapoint.
 *
 * @param regs          The registers
 */
void
isr_breakpoint(UNUSED registers_t *regs)
{
    KPRINTF_DEBUG("A breakpoint has been triggered.");
}
