/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel Source file main
*/

#include "kernel/interruption/idt.h"
#include "kernel/tty/tty.h"

/**
 * @brief Kernel main entry point.
 *        This function is located at 0x10000 in the memory.
 *        This function is called by the kernel_entry.s source file.
 */
void
kmain(void)
{
    KDEBUG_TTY("$> Welcome to Del'OS Kernel Space.");
    KERROR_TTY("This kernel is still in development...");
    kidt_create_ptr(&idt_ptr);
    kidt_load_cpu(&idt_ptr);
    while (1);
    return;
}
