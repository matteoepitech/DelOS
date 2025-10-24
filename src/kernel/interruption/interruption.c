/*
** EPITECH PROJECT, 2025
** src/kernel/interruption/interruption
** File description:
** Interruption source file
*/

#include "kernel/interruption/interruption.h"

/**
 * @brief Stop the interruptions by clearing the interruption flag.
 *        cli -> clear interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kstop_interruption_extern(void)
{
    __asm__ volatile ("cli");
}

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 *        This only manage the external interruptions like IRQs.
 */
void
kstart_interruption_extern(void)
{
    __asm__ volatile ("sti");
}
