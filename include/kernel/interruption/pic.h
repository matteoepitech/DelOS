/*
** DELOS PROJECT, 2025
** include/kernel/interruption/pic
** File description:
** PIC header file
*/

#include "types.h"

#ifndef KERNEL_INTERRUPTION_PIC_H_
    #define KERNEL_INTERRUPTION_PIC_H_

/**
 * @brief Remap the whole PIC interface to permit no collision between the ISR and IRQ.
 */
void
kpic_remap(void);

/**
 * @brief Set the bit mask of the IRQ to 1 = blocked.
 *
 * @param irq_line              The IRQ number
 */
void
kpic_set_mask(uint8_t irq_line);

/**
 * @brief Set the bit mask of the IRQ to 0 = activated.
 *
 * @param irq_line              The IRQ number
 */
void
kpic_clear_mask(uint8_t irq_line);

#endif /* ifndef KERNEL_INTERRUPTION_PIC_H_ */
