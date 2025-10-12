/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel Source file main
*/

#include "drivers/video/vga.h"
#include "kernel/tty/tty.h"

/**
 * @brief Kernel main entry point.
 *        This function is located at 0x10000 in the memory.
 *        This function is called by the kernel_entry.s source file.
 */
void
kmain(void)
{
    tty_puts("$> ", VGA_GREEN_FOREGROUND | VGA_BLACK_BACKGROUND);
    tty_puts("Welcome to DelOS's kernel!", VGA_TEXT_DEFAULT_COLOR);
    while (1);
    return;
}
