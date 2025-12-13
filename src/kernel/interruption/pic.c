/*
** DELOS PROJECT, 2025
** src/kernel/interruption/pic
** File description:
** PIC source file
*/

#include "kernel/interruption/pic.h"
#include "utils/asm/io_port.h"

/**
 * @brief Remap the whole PIC interface to permit no collision between the ISR and IRQ.
 */
void
kpic_remap(void)
{
    outb(PIC1_COMMAND_PORT, 0x11);     // Init PIC primary
    outb(PIC2_COMMAND_PORT, 0x11);     // Init PIC secondary
    outb(0x21, 0x20);                  // Offset of primary is now 0x20 (idt number 32)
    outb(0xA1, 0x28);                  // Offset of secondary is now 0x28 (idt number 40)
    outb(0x21, 0x04);                  // Set the secondary PIC to the IRQ2
    outb(0xA1, 0x02);                  // Say to secondary PIC his identifier (IRQ2)
    outb(0x21, 0x01);                  // Set the mode 8086/88
    outb(0xA1, 0x01);                  // Set the mode 8086/88
    outb(0x21, 0x0);                   // Reactivate all PIC primary
    outb(0xA1, 0x0);                   // Reactivate all PIC secondary
    // Set all masks for the 8 first IRQs for the primary PIC
    kpic_clear_mask(0);
    kpic_clear_mask(1);
    kpic_set_mask(2);
    kpic_set_mask(3);
    kpic_set_mask(4);
    kpic_set_mask(5);
    kpic_set_mask(6);
    kpic_set_mask(7);
}

/**
 * @brief Set the bit mask of the IRQ to 1 = blocked.
 *        NOTE: Maybe the outb will not works for IRQ > 8 since it's byte
 *
 * @param irq_line              The IRQ number
 */
void
kpic_set_mask(uint8_t irq_line)
{
    uint16_t port;
    uint8_t value;

    if (irq_line < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        irq_line -= 8;
    }
    value = inb(port) | (1 << irq_line);
    outb(port, value);
}

/**
 * @brief Set the bit mask of the IRQ to 0 = activated.
 *        NOTE: Maybe the outb will not works for IRQ > 8 since it's byte
 *
 * @param irq_line              The IRQ number
 */
void
kpic_clear_mask(uint8_t irq_line)
{
    uint16_t port;
    uint8_t value;

    if (irq_line < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        irq_line -= 8;
    }
    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}
