/*
** DELOS PROJECT, 2025
** src/kernel/interruption/irq/irq_timer
** File description:
** IRQ timer (IRQ0)
*/

#include "kernel/interruption/isr.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief IRQ timer.
 * 
 * @param regs          The registers
 */
void
irq_timer(UNUSED registers_t *regs)
{
    // TODO: Timer handling
    return;
}
