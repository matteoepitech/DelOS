/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_div_zero
** File description:
** ISR div zero
*/

#include "kernel/misc/panic.h"
#include "kernel/tty/tty.h"
#include "defines.h"
#include "types.h"

/**
 * @brief ISR division by zero.
 *
 * @param int_no                The interruption number
 * @param err_code              The error code if provided
 */
void
isr_div_zero(UNUSED uint32_t int_no, UNUSED uint32_t err_code)
{
    KPANIC("Division by zero.");
}
