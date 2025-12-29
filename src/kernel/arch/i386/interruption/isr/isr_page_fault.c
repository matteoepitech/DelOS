/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/isr/isr_page_fault
** File description:
** ISR breakpoint
*/

#include <kernel/arch/i386/interruption/isr.h>
#include <kernel/misc/panic.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief ISR breapoint.
 *
 * @param regs          The registers
 */
void
isr_page_fault(registers_t *regs)
{
    KPANIC("Page fault invoked...");
}
