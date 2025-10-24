/*
** DELOS PROJECT, 2025
** src/kernel/interruption/irq/irq_keyboard_press
** File description:
** IRQ keyboard press (IRQ1)
*/

#include "kernel/interruption/isr.h"
#include "utils/asm/io_port.h"
#include "kernel/tty/tty.h"
#include "defines.h"

// TODO: Need to be changed considering the localization AZERTY/QWERTY
static unsigned char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\','z',
    'x','c','v','b','n','m',',','.','/', 0, '*', 0,' '
};

/**
 * @brief IRQ keyboard press.
 * 
 * @param regs          The registers
 */
void
irq_keyboard_press(UNUSED registers_t *regs)
{
    uint8_t code = inb(0x60);

    if (!(code & 0x80) && code < 128) {
        ktty_putc(scancode_to_ascii[code], VGA_TEXT_DEFAULT_COLOR);
    }
    outb(0x20, 0x20);
}
