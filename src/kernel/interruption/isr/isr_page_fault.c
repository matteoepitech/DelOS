/*
** DELOS PROJECT, 2025
** src/kernel/interruption/isr/isr_page_fault
** File description:
** ISR breakpoint
*/

#include <kernel/interruption/isr.h>
#include <utils/kstdlib/kstdio.h>
#include <kernel/misc/panic.h>
#include <kernel/memory/mmu.h>
#include <kernel/tty/tty.h>
#include <defines.h>

/**
 * @brief ISR breapoint.
 *
 * @param regs          The registers
 */
void
isr_page_fault(UNUSED isr_registers_t *regs)
{
    char buffer[64] = {0};

    ksprintf(buffer, "Page fault invoked by accessing the address %x.", kmmu_get_cr2());
    if (buffer[63] != 0) {
        KPANIC("Page fault invoked without getting access to the address (buffer too small).");
        return;
    }
    KPANIC(buffer);
}
