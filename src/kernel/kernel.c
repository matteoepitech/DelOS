/*
** DELOS PROJECT, 2025
** src/kernel/kernel
** File description:
** Kernel Source file main
*/

#include <kernel/arch/i386/interruption/interruption.h>
#include <kernel/memory/early_allocator/early_alloc.h>
#include <kernel/arch/i386/interruption/idt.h>
#include <kernel/arch/i386/interruption/pic.h>
#include <kernel/memory/pmm/pmm.h>
#include <kernel/memory/vmm/vmm.h>
#include <kernel/shell/shell.h>
#include <kernel/misc/panic.h>
#include <utils/misc/print.h>
#include <utils/asm/hlt.h>
#include <defines.h>

/**
 * @brief Kernel main entry point.
 *        This function is located at 0x10000 in the memory.
 *        This function is called by the kernel_entry.s source file.
 */
void
kmain(void)
{
    kinterruption_extern_stop();
    kpic_remap();
    kidt_create_ptr(&idt_ptr);
    kidt_load_cpu(&idt_ptr);
    kpit_timer_init(PIT_TARGET_FREQUENCY);
    ktty_cursor_set_visibility(OK_TRUE);

    kinterruption_extern_start(); // THIS IS FUCK

    make_hlt_hard_no_msg(); // Should stop here
    kshell_start();

    kearly_malloc_disable(); // NEVER GOES HERE for the moment

    KHLT_HARD_DO();
    return;
}
