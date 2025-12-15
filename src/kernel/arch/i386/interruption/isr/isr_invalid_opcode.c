/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/isr/isr_invalid_opcode
** File description:
** ISR invalid opcode
*/

#include "kernel/arch/i386/interruption/isr.h"
#include "kernel/misc/panic.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief ISR invalid opcode.
 *
 * @param regs          The registers
 */
void
isr_invalid_opcode(UNUSED registers_t *regs)
{
    KPANIC("CPU just ran into an invalid opcode.");
}
