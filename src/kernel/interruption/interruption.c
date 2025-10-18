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
 */
void
kstop_interruption(void)
{
    __asm__ volatile ("cli");
}

/**
 * @brief Start the interruptions by setting the interruption flag.
 *        sti -> set interruption flag
 */
void
kstart_interruption(void)
{
    __asm__ volatile ("sti");
}
