/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel main
*/

#include "kernel/tty/tty.h"

/**
 * @brief Kernel main entry point.
 *        This function is located at 0x10000 in the memory.
 *        This function is called by the kernel_entry.s source file.
 */
void kmain(void)
{
    tty_putc_at(0, 0, 'H', 0x00);
    tty_putc_at(1, 0, 'e', 0x00);
    tty_putc_at(2, 0, 'l', 0x00);
    tty_putc_at(3, 0, 'l', 0x00);
    tty_putc_at(4, 0, 'o', 0x00);

    while (1);
    return;
}
