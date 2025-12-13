/*
** DELOS PROJECT, 2025
** src/kernel/interruption/irq/irq_keyboard_press
** File description:
** IRQ keyboard press (IRQ1)
*/

#define KEYBOARD_LAYOUT_AZERTY

#include "kernel/interruption/pic.h"
#include "kernel/interruption/isr.h"
#include "kernel/misc/keyboard.h"
#include "utils/asm/io_port.h"
#include "kernel/tty/tty.h"
#include "defines.h"

#if defined(KEYBOARD_LAYOUT_QWERTY)

static const uint8_t scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\','z',
    'x','c','v','b','n','m',',','.','/', 0, '*', 0,' '
};

#elif defined(KEYBOARD_LAYOUT_AZERTY)

static const uint8_t scancode_to_ascii[128] = {
    0,  27, '&', 0x82, '"', '\'', '(', '-', 0x8A, '_', 0x87, 0x85, ')', '=', '\b',  // é, è, ç, à
    '\t','a','z','e','r','t','y','u','i','o','p','^','$','\n', 0,
    'q','s','d','f','g','h','j','k','l','m', 0x97, 0x88, 0, '*','w',
    'x','c','v','b','n',',',';','.', '/', 0, '*', 0,' '
};

#else
    #error "Please define KEYBOARD_LAYOUT_AZERTY or KEYBOARD_LAYOUT_QWERTY"
#endif

int8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE] = {0};
size_t keyboard_head = 0;
size_t keyboard_tail = 0;

/**
 * @brief Push the ascii character to the circular buffer.
 *
 * @param c             The ascii
 */
void
kkeyboard_push(char c)
{
    size_t next = (keyboard_head + 1) % KEYBOARD_BUFFER_SIZE;

    if (next != keyboard_tail) {
        keyboard_buffer[keyboard_head] = c;
        keyboard_head = next;
    }
}

/**
 * @brief Pop the tail character from the circular buffer.
 *
 * @return The ascii character.
 */
int32_t
kkeyboard_pop(void)
{
    if (keyboard_head == keyboard_tail)
        return -1;
    int32_t c = keyboard_buffer[keyboard_tail];
    keyboard_tail = (keyboard_tail + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}

/**
 * @brief IRQ for keyboard press.
 *
 * @param regs          The registers
 */
void
irq_keyboard_press(UNUSED registers_t *regs)
{
    uint8_t code = inb(0x60);

    if (!(code & 0x80) && code < 128) {
        uint8_t ascii = scancode_to_ascii[code];
        if (ascii != 0x0) {
            kkeyboard_push(ascii);
        }
    }
    PIC_CALL_EOI();
}
