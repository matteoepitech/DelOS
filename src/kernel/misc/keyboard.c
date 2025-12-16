/*
** DELOS PROJECT, 2025
** src/kernel/misc/keyboard
** File description:
** Keyboard source file
*/

#include "kernel/arch/i386/interruption/interruption.h"
#include "kernel/misc/keyboard.h"
#include "utils/asm/hlt.h"

/**
 * @brief Get a character from the keyboard circular buffer.
 *        Or wait until a character pop out.
 *
 * @return The character ascii.
 */
uint8_t
kkeyboard_getchar(void)
{
    int8_t character = kkeyboard_pop();

    while (character == -1) {
        kinterruption_extern_start();
        KHLT_DO();
        character = kkeyboard_pop();
    }
    return (uint8_t) character;
}
