/*
** EPITECH PROJECT, 2025
** src/kernel/interruption/idt
** File description:
** IDT source file
*/

#include "kernel/interruption/idt.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Variable for the IDT pointer loaded in the CPU.
 *        This contains the size and address of the IDT.
 */
idt_ptr_t idt_ptr = {0};

/**
 * @brief Variable for the IDT values loaded in the CPU.
 *        This contains all of the entries of the IDT.
 */
idt_entry_t idt[IDT_SIZE];

/**
 * @brief Took the pointer passed as parameter and set his memory values.
 *
 * @param idt_ptr       The pointer to the future IDT
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kidt_create_ptr(idt_ptr_t *ptr)
{
    if (ptr == NULL) {
        return KO_FALSE;
    }
    ptr->_limit = (sizeof(idt_entry_t) * IDT_SIZE) - 1;
    ptr->_base = (uint32_t) &idt;
    return OK_TRUE;
}

/**
 * @brief Load the idt_ptr in the CPU using lidt instruction.
 *
 * @param idt_ptr       The pointer to the future IDT
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kidt_load_cpu(idt_ptr_t *ptr)
{
    idt_ptr_t idt_ptr_check = {0};

    if (ptr == NULL) {
        return KO_FALSE;
    }
    if (ptr->_base == NULL || ptr->_limit == 0) {
        KERROR_TTY("IDT's pointer is not created. Aborting...");
        return KO_FALSE;
    }
    __asm__ volatile ("lidt %0" : : "m"(*ptr));
    __asm__ volatile ("sidt %0" : "=m"(idt_ptr_check));
    if (idt_ptr_check._base == NULL) {
        KERROR_TTY("IDT is not loaded correctly.")
        return KO_FALSE;
    }
    return OK_TRUE;
}
