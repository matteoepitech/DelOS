/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/isr/isr_div_zero
** File description:
** ISR div zero
*/

#include "kernel/arch/i386/interruption/isr.h"
#include "kernel/misc/panic.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief ISR division by zero.
 *
 * @param regs          The registers
 */
void
isr_div_zero(UNUSED registers_t *regs)
{
    KPANIC("Division by zero.");
}
