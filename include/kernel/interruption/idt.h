/*
** DELOS PROJECT, 2025
** include/kernel/interruption/idt
** File description:
** IDT header file
*/

#include "types.h"

#ifndef KERNEL_INTERRUPTION_IDT_H_
    #define KERNEL_INTERRUPTION_IDT_H_

    // The size of the IDT this means we have X entries availables.
    #define IDT_SIZE 256

/**
 * @brief Structure for an IDT entry.
 *        -offset_low  = The low part of the address handler
 *        -selector    = Which segment we run it (CS for exemple)
 *        -zero        = needed zero padding
 *        -type_attr   = Type & flags (0x8e for a normal interrupt)
 *        -offset_high = The high part of the address handler
 */
typedef struct idt_entry_s {
    uint16_t _offset_low;
    uint16_t _selector;
    uint8_t _zero;
    uint8_t _type_attr;
    uint16_t _offset_high;
} __attribute__((packed)) idt_entry_t;


/**
 * @brief Structure for the IDT register stuff.
 *        -limit = The size of the interruption descriptor table in bytes
 *        -base  = The start address of the interruption description table
 *        This structure need to be 6 bytes since the instruction LIDT in x86
 *        is designed to take 2 bytes for the limit and 4 bytes for the base.
 */
typedef struct idt_ptr_s {
    uint16_t _limit;
    uint32_t _base;
} __attribute__((packed)) idt_ptr_t;

/**
 * @brief Variable for the IDT pointer loaded in the CPU.
 *        This contains the size and address of the IDT.
 *
 *        Declared in src/kernel/interruption/idt.c
 */
extern idt_ptr_t idt_ptr;

/**
 * @brief Variable for the IDT values loaded in the CPU.
 *        This contains all of the entries of the IDT.
 *
 *        Declared in src/kernel/interruption/idt.c
 */
extern idt_entry_t idt[IDT_SIZE];

/**
 * @brief Took the pointer passed as parameter and set his memory values.
 *
 * @param idt_ptr_local         The pointer to the future IDT
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kidt_create_ptr(idt_ptr_t *ptr);

/**
 * @brief Load the idt_ptr in the CPU using lidt instruction.
 *
 * @param idt_ptr               The pointer to the future IDT
 *
 * @return OK_TRUE if worked, KO_FALSE otherwise.
 */
bool32_t
kidt_load_cpu(idt_ptr_t *ptr);

#endif /* ifndef KERNEL_INTERRUPTION_IDT_H_ */
