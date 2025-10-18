/*
** EPITECH PROJECT, 2025
** src/kernel/interruption/idt
** File description:
** Interruption descriptor table source file
*/

#include "kernel/interruption/idt.h"
#include "kernel/interruption/isr.h"
#include "utils/kstdlib/kmemory.h"
#include "kernel/tty/tty.h"
#include "defines.h"

/**
 * @brief Variable for the IDT pointer loaded in the CPU.
 *        This contains the size and address of the IDT.
 */
idt_ptr_t idt_ptr;

/**
 * @brief Variable for the IDT values loaded in the CPU.
 *        This contains all of the entries of the IDT.
 */
idt_entry_t idt[IDT_SIZE];

// division by zero
extern void isr0();
extern void isr_div_zero(registers_t *regs);
// debug exception
extern void isr1();
extern void isr_debug_exception(registers_t *regs);
// breakpoint
extern void isr3();
extern void isr_breakpoint(registers_t *regs);

/**
 * @brief Load all interruption service routine before the load in CPU.
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
static bool32_t
idt_load_all_isr(void)
{
    // division by zero
    if (kidt_set_entry(0, (uint32_t) isr0, 0x08, IDT_INT_GATE_KERNEL) == KO_FALSE)
        return KO_FALSE;
    if (kisr_register_handler(0, isr_div_zero) == KO_FALSE)
        return KO_FALSE;
    // debug exception
    if (kidt_set_entry(1, (uint32_t) isr1, 0x08, IDT_INT_GATE_KERNEL) == KO_FALSE)
        return KO_FALSE;
    if (kisr_register_handler(1, isr_debug_exception) == KO_FALSE)
        return KO_FALSE;
    // breakpoint
    if (kidt_set_entry(3, (uint32_t) isr3, 0x08, IDT_INT_GATE_KERNEL) == KO_FALSE)
        return KO_FALSE;
    if (kisr_register_handler(3, isr_breakpoint) == KO_FALSE)
        return KO_FALSE;
    return OK_TRUE;
}

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
    kmemset(&idt, 0, sizeof(idt_entry_t) * IDT_SIZE - 1);
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
    if (idt_load_all_isr() == KO_FALSE) {
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

/**
 * @brief Set an interruption in the IDT at the index.
 *
 * @param index                 The index in the IDT of this interruption
 * @param addr                  The address to jump at
 * @param selector              The segment to be at (segment code most of time)
 * @param type_attr             The attributes of this interruption
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kidt_set_entry(uint8_t index, uint32_t addr, uint16_t selector, uint8_t type_attr)
{
    if (addr == NULL) {
        return KO_FALSE;
    }
    idt[index]._offset_high = (addr & 0xFFFF0000) >> 16;
    idt[index]._offset_low = addr & 0x0000FFFF;
    idt[index]._selector = selector;
    idt[index]._type_attr = type_attr;
    idt[index]._zero = 0;
    return OK_TRUE;
}
