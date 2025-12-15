/*
** DELOS PROJECT, 2025
** include/kernel/arch/i386/interruption/pic
** File description:
** PIC header file
*/

#include "utils/asm/io_port.h"

#ifndef KERNEL_INTERRUPTION_PIC_H_
    #define KERNEL_INTERRUPTION_PIC_H_

    // PIC commands primary port and secondary port
    #define PIC1_COMMAND_PORT        0x20
    #define PIC2_COMMAND_PORT        0xA0

    // PIC End of Interrupt
    #define PIC_EOI        0x20
    #define PIC_CALL_EOI() kpic_send_eoi()

/**
 * @brief Remap the whole PIC interface to permit no collision between the ISR and IRQ.
 */
void
kpic_remap(void);

/**
 * @brief Set the bit mask of the IRQ to 1 = blocked.
 *
 * @param irq_line              The IRQ number
 */
void
kpic_set_mask(uint8_t irq_line);

/**
 * @brief Set the bit mask of the IRQ to 0 = activated.
 *
 * @param irq_line              The IRQ number
 */
void
kpic_clear_mask(uint8_t irq_line);

/**
 * @brief Send an End of Interrupt 
 */
static inline void
kpic_send_eoi(void)
{
    outb(PIC1_COMMAND_PORT, PIC_EOI);
}

#endif /* ifndef KERNEL_INTERRUPTION_PIC_H_ */
