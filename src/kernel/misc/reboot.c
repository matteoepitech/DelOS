/*
** DELOS PROJECT, 2025
** src/kernel/misc/reboot
** File description:
** Reboot source file
*/

#include <kernel/arch/i386/interruption/interruption.h>
#include <kernel/misc/reboot.h>
#include <kernel/misc/panic.h>
#include <utils/asm/io_port.h>
#include <types.h>

/**
 * @brief Helper function for rebooting the machine.
 */
void
kreboot(void)
{
    uint8_t tmp = 0x02;

    kinterruption_extern_stop();
    while (tmp & 0x02){
        tmp = inb(0x64);
    }
    outb(0x64, 0xFE);
    KPANIC("Reboot failed.");
}
