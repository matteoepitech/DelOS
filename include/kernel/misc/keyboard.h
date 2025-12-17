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

extern int8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern size_t keyboard_head;
extern size_t keyboard_tail;

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

#endif
