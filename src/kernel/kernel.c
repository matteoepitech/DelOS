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
    ktty_puts("$> ", VGA_GREEN_FOREGROUND | VGA_BLACK_BACKGROUND);
    ktty_puts("Welcome to DelOS's kernel!", VGA_TEXT_DEFAULT_COLOR);
    ktty_puts("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO", VGA_TEXT_DEFAULT_COLOR);
    ktty_puts("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaajjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", VGA_TEXT_DEFAULT_COLOR);
    ktty_putc('M', VGA_RED_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_putc('M', VGA_RED_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_putc_at(40, 12, 'm', VGA_RED_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_putc('M', VGA_RED_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_puts("salut", VGA_GREEN_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_puts_at(41, 12, "salutoooooooooooooooooooooooooooooooooooooooooooooooooo", VGA_GREEN_BACKGROUND | VGA_BLUE_FOREGROUND);
    ktty_puts_at(3, 13, "salutoooooooooooooooooooooooooooooooooooooooooooooooooo", VGA_BLUE_BACKGROUND | VGA_BLUE_FOREGROUND);
    while (1);
    return;
}
