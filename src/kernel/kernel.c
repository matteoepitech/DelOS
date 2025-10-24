/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel Source file main
*/

#include "kernel/interruption/idt.h"
#include "kernel/interruption/interruption.h"
#include "kernel/interruption/pic.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Kernel main entry point.
 *        This function is located at 0x10000 in the memory.
 *        This function is called by the kernel_entry.s source file.
 */
void
kmain(void)
{
    kstop_interruption_extern();
    kpic_remap();
    kidt_create_ptr(&idt_ptr);
    kidt_load_cpu(&idt_ptr);
    kstart_interruption_extern();

    KDEBUG_TTY("$> Welcome to Del'OS Kernel Space.");
    ktty_cursor_set_visibility(OK_TRUE);
    while (1);
    return;
}
