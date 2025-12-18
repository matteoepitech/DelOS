/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/irq/irq_keyboard_press
** File description:
** IRQ keyboard press (IRQ1)
*/

#define KEYBOARD_LAYOUT_AZERTY

#include "kernel/arch/i386/interruption/pic.h"
#include "kernel/arch/i386/interruption/isr.h"
#include "kernel/misc/keyboard.h"
#include "utils/asm/io_port.h"
#include "utils/misc/print.h"
#include "kernel/tty/tty.h"
#include "defines.h"

#if defined(KEYBOARD_LAYOUT_QWERTY)

static const uint8_t scancode_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const uint8_t scancode_to_ascii_shift[128] = {
    0x00, 0x1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0x00,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0x00, '|', 'Z',
    'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0x00, '*', 0x00, ' '
};

#elif defined(KEYBOARD_LAYOUT_AZERTY)

static const uint8_t scancode_to_ascii[128] = {
    0x00, 0x1B, '&', 0x82, '"', '\'', '(', '-', 0x8A, '_', 0x87, 0x85, ')', '=', '\b',
    '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0x00,
    'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x97, 0x88, 0x00, '*', 'w',
    'x', 'c', 'v', 'b', 'n', ',', ';', '.', '/', 0x00, '*', 0x00, ' '
};

static const uint8_t scancode_to_ascii_shift[128] = {
    0x00, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0xB0, '+', '\b',
    '\t', 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0xA8, 0xA3, '\n', 0x00,
    'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', 0xB5, 0x00, '*','W',
    'X', 'C', 'V', 'B', 'N', '?', '.', '/', 0xA7, 0x00, '*', 0x00, ' '
};


#else
    #error "Please define KEYBOARD_LAYOUT_AZERTY or KEYBOARD_LAYOUT_QWERTY"
#endif

#ifndef KEY_IS_PRESSED
    #define KEY_IS_PRESSED(x) (!(x & 0x80))
#endif /* ifndef KEY_IS_PRESSED */

#ifndef KEY_IS_RELEASED
    #define KEY_IS_RELEASED(x) (x & 0x80)
#endif /* ifndef KEY_IS_RELEASED */

#ifndef KEY_SHIFTS
    #define KEY_LEFT_SHIFT 0x2A
    #define KEY_RIGHT_SHIFT 0x36
#endif /* ifndef KEY_SHIFTS */

#ifndef KEY_CAPS_LOCK
    #define KEY_CAPS_LOCK 0x3A
#endif /* ifndef KEY_CAPS_LOCK */

/* Keyboard manager using a head/tail management and fixed buffer */
int8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE] = {0};
size_t keyboard_head = 0;
size_t keyboard_tail = 0;
bool32_t shift_pressed = KO_FALSE;
bool32_t caps_lock_activated = KO_FALSE;

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
    int32_t c = 0;

    if (keyboard_head == keyboard_tail)
        return -1;
    c = keyboard_buffer[keyboard_tail];
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

    if (KEY_IS_PRESSED(code)) {
        if (code == KEY_LEFT_SHIFT || code == KEY_RIGHT_SHIFT) {
            shift_pressed = OK_TRUE;
        } else {
            if (code == KEY_CAPS_LOCK) {
                caps_lock_activated = caps_lock_activated ^ 1;
            } else if ((shift_pressed == OK_TRUE) ^ caps_lock_activated) {
                if (scancode_to_ascii_shift[code] != 0x00) {
                    kkeyboard_push(scancode_to_ascii_shift[code]);
                }
            } else {
                if (scancode_to_ascii[code] != 0x00) {
                    kkeyboard_push(scancode_to_ascii[code]);
                }
            }
        }
    } else if ((code ^ 0x80) == KEY_LEFT_SHIFT || (code ^ 0x80) == KEY_RIGHT_SHIFT) {
        shift_pressed = KO_FALSE;
    }
    PIC_CALL_EOI();
}
