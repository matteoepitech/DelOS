/*
** DELOS PROJECT, 2025
** src/kernel/interruption/irq/irq_keyboard_press
** File description:
** IRQ keyboard press (IRQ1)
*/

#include <kernel/interruption/pic.h>
#include <kernel/interruption/isr.h>
#include <kernel/misc/keyboard.h>
#include <utils/asm/io_port.h>
#include <utils/misc/print.h>
#include <kernel/tty/tty.h>
#include <defines.h>

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
keymap_t keymap = KKEYMAP_AZERTY;
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
irq_keyboard_press(UNUSED isr_registers_t *regs)
{
    uint8_t code = inb(0x60);
    uint8_t *scancodes = kkeyboard_get_keymap_values(keymap, shift_pressed ^ caps_lock_activated);

    if (KEY_IS_PRESSED(code)) {
        if (code == KEY_LEFT_SHIFT || code == KEY_RIGHT_SHIFT) {
            shift_pressed = OK_TRUE;
        } else {
            if (code == KEY_CAPS_LOCK) {
                caps_lock_activated = caps_lock_activated ^ 1;
            } else if (scancodes[code] != 0x00) {
                kkeyboard_push(scancodes[code]);
            }
        }
    } else if ((code ^ 0x80) == KEY_LEFT_SHIFT || (code ^ 0x80) == KEY_RIGHT_SHIFT) {
        shift_pressed = KO_FALSE;
    }
    PIC_CALL_EOI();
}
