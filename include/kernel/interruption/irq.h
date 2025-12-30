/*
** DELOS PROJECT, 2025
** include/kernel/interruption/irq
** File description:
** Interruption request header file
*/

#ifndef KERNEL_INTERRUTPION_IRQ_H_
    #define KERNEL_INTERRUTPION_IRQ_H_

    // This macro is used for declaring interruption service routine from stubs
    #ifndef IRQ_DECLARE_STUB
        #define IRQ_DECLARE_STUB(nb) extern void irq##nb(void)
    #endif /* ifndef IRQ_DECLARE_STUB */

    // This macro is used for declaring interruption service routine easier
    #ifndef IRQ_DECLARE_HANDLER
        #define IRQ_DECLARE_HANDLER(name) extern void name(registers_t *regs)
    #endif /* ifndef IRQ_DECLARE_HANDLER */

#endif /* ifndef KERNEL_INTERRUTPION_IRQ_H_ */
