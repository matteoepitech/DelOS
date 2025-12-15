/*
** DELOS PROJECT, 2025
** include/kernel/arch/i386/interruption/pit
** File description:
** PIT header file
*/

#include "utils/asm/io_port.h"

#ifndef KERNEL_INTERRUPTION_PIT_H_
    #define KERNEL_INTERRUPTION_PIT_H_

    // Base frequency in hertz of the PIT
    #define PIT_FREQUENCY           1193180
    // Target frequency in ticks per seconds
    #define PIT_TARGET_FREQUENCY    100
    // PIT command port and data port
    #define PIT_COMMAND_PORT        0x43
    #define PIT_DATA_PORT           0x40

// @brief The ticks count of since start of the kernel.
extern volatile uint32_t ticks_count;
// @brief The seconds count of since start of the kernel.
extern volatile uint32_t seconds_count;

/**
 * @brief Init the timer for the PIT (Programmable Interval Timer).
 *
 * @param frequency The frequency needed for the PIT
 */
void
kpit_timer_init(uint32_t frequency);

#endif /* ifndef KERNEL_INTERRUPTION_PIT_H_ */
