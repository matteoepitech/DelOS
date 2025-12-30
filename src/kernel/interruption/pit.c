/*
** DELOS PROJECT, 2025
** src/kernel/interruption/pit
** File description:
** PIT source file
*/

#include <kernel/interruption/pit.h>
#include <kernel/misc/panic.h>
#include <utils/asm/io_port.h>

// @brief The ticks count of since start of the kernel.
volatile uint32_t ticks_count = 0;
// @brief The seconds count of since start of the kernel.
volatile uint32_t seconds_count = 0;

/**
 * @brief Init the timer for the PIT (Programmable Interval Timer).
 *        The divisor can be at maximum 65535 so even with frequency of 1 tick
 *        per second it will be truncated to 65535 which is basically ~88 ticks per seconds
 *
 *        The value 0x36 on the pit command port means :
 *            - Canal 0 (bits 6-7 = 00)
 *            - Access mode low/high byte (bits 4-5 = 11)
 *            - Square wave generator mode (bits 1-3 = 011)
 *            - Binary mode (bit 0 = 0)
 *
 * @param frequency The frequency needed for the PIT
 */
void
kpit_timer_init(uint32_t frequency)
{
    uint16_t divisor = 0;

    if (frequency <= 0) {
        KPANIC("A bad PIT frequency has been passed.");
        return;
    }
    divisor = PIT_FREQUENCY / frequency;
    outb(PIT_COMMAND_PORT, 0x36);
    outb(PIT_DATA_PORT, (uint8_t) (divisor));
    outb(PIT_DATA_PORT, (uint8_t) (divisor >> 8));
}
