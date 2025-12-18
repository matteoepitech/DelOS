/*
** DELOS PROJECT, 2025
** include/kernel/misc/keyboard
** File description:
** Keyboard header file
*/

#include "types.h"

#ifndef KERNEL_MISC_KEYBOARD_H_
    #define KERNEL_MISC_KEYBOARD_H_

    #ifndef KEYBOARD_BUFFER_SIZE
        #define KEYBOARD_BUFFER_SIZE 128
    #endif /* ifndef KEYBOARD_BUFFER_SIZE */

/*
 * @brief This enum contain every keyboard layout implemented in the kernel IRQ.
 */
typedef enum {
    KEYMAP_QWERTY,
    KEYMAP_AZERTY,
} keymap_t;

/* Some extern variables most used in the IRQ directly but can be used outside */
extern keymap_t keymap;
extern int8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern size_t keyboard_head;
extern size_t keyboard_tail;
extern bool32_t shift_pressed;
extern bool32_t caps_lock_activated;

/**
 * @brief Push the ascii character to the circular buffer.
 *
 * @param c             The ascii
 */
void
kkeyboard_push(char c);

/**
 * @brief Pop the tail character from the circular buffer.
 *
 * @return The ascii character.
 */
int32_t
kkeyboard_pop(void);

/**
 * @brief Get a character from the keyboard circular buffer.
 *        Or wait until a character pop out.
 *
 * @return The character ascii.
 */
char
kkeyboard_getchar(void);

/**
 * @brief Get the keyboard values based on the enum passed as parameter.
 *
 * @param keymap     The keymap enumeration containing every implemented keymap
 * @param shifted    If the keymap values wanted is shifted or not
 *
 * @return A pointer to the keymap values supposed to be initialized in a persistant data section.
 */
uint8_t *
kkeyboard_get_keymap_values(keymap_t keymap, bool32_t shifted);

#endif
