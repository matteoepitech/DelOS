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
    tty_puts_at(0, 0, "Hello World!", VGA_TEXT_DEFAULT_COLOR);
    while (1);
    return;
}
