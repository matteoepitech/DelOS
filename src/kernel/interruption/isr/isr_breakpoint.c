/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_breakpoint
** File description:
** ISR breakpoint
*/

#include "kernel/interruption/isr.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief ISR breapoint.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided
 */
void
isr_breakpoint(UNUSED registers_t *regs)
{
    KDEBUG_TTY("Got a breakpoint");
}
