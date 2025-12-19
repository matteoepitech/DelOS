/*
** DELOS PROJECT, 2025
** src/kernel/arch/i386/interruption/interruption
** File description:
** Interruption source file
*/

#include <kernel/arch/i386/interruption/interruption.h>

/**
 * @brief Stop the interruptions by clearing the interruption flag.
 *        cli -> clear interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kinterruption_extern_stop(void)
{
    __asm__ volatile ("cli");
}

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kinterruption_extern_start(void)
{
    __asm__ volatile ("sti");
}
