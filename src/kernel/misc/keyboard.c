/*
** DELOS PROJECT, 2025
** src/kernel/misc/keyboard
** File description:
** Keyboard source file
*/

#include "kernel/arch/i386/interruption/interruption.h"
#include "kernel/misc/keyboard.h"
#include "utils/asm/hlt.h"

/* WARN: Requires i8042-compatible keyboard controller (PS/2 legacy mode). */

static const uint8_t scancode_to_ascii_qwerty[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const uint8_t scancode_to_ascii_qwerty_shift[128] = {
    0x00, 0x1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0x00,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0x00, '|', 'Z',
    'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0x00, '*', 0x00, ' '
};

static const uint8_t scancode_to_ascii_azerty[128] = {
    0x00, 0x1B, '&', 0x82, '"', '\'', '(', '-', 0x8A, '_', 0x87, 0x85, ')', '=', '\b',
    '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0x00,
    'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x97, 0x88, 0x00, '*', 'w',
    'x', 'c', 'v', 'b', 'n', ',', ';', '.', '/', 0x00, '*', 0x00, ' '
};

static const uint8_t scancode_to_ascii_azerty_shift[128] = {
    0x00, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0xB0, '+', '\b',
    '\t', 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0xA8, 0xA3, '\n', 0x00,
    'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', 0xB5, 0x00, '*','W',
    'X', 'C', 'V', 'B', 'N', '?', '.', '/', 0xA7, 0x00, '*', 0x00, ' '
};

/**
 * @brief Get the keyboard values based on the enum passed as parameter.
 *
 * @param keymap     The keymap enumeration containing every implemented keymap
 * @param shifted    If the keymap values wanted is shifted or not
 *
 * @return A pointer to the keymap values supposed to be initialized in a persistant data section.
 */
uint8_t *
kkeyboard_get_keymap_values(keymap_t keymap, bool32_t shifted)
{
    switch (keymap) {
        case KEYMAP_QWERTY:
            if (shifted)
                return (uint8_t *) &scancode_to_ascii_qwerty_shift;
            else
                return (uint8_t *) &scancode_to_ascii_qwerty;
        case KEYMAP_AZERTY:
            if (shifted)
                return (uint8_t *) &scancode_to_ascii_azerty_shift;
            else
                return (uint8_t *) &scancode_to_ascii_azerty;
    }
    if (shifted)
        return (uint8_t *) &scancode_to_ascii_qwerty_shift;
    else
        return (uint8_t *) &scancode_to_ascii_qwerty;
}

/**
 * @brief Get a character from the keyboard circular buffer.
 *        Or wait until a character pop out.
 *
 * @return The character ascii.
 */
char
kkeyboard_getchar(void)
{
    char character = kkeyboard_pop();

    while (character == -1) {
        kinterruption_extern_start();
        KHLT_DO();
        character = kkeyboard_pop();
    }
    return (char) character;
}
