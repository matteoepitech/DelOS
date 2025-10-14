/*
** DELOS PROJECT, 2025
** include/utils/asm/io_port
** File description:
** IO Port header file
*/

#include "types.h"

#ifndef IO_PORT_H_
    #define IO_PORT_H_

/**
 * @brief Output port call to a port and his value.
 *
 * @param port          The port to write on
 * @param val           The value
 */
static inline void
outb(uint16_t port, uint8_t val)
{
    // AT&T syntax used by GCC
    // outb source, destination
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * @brief Input port call to a port.
 *
 * @param port          The port to read on
 *
 * @return The value we got from the port.
 */
static inline uint8_t
inb(uint16_t port)
{
    uint8_t r = 0;

    // AT&T syntax used by GCC
    // inb source, destination
    __asm__ volatile ("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

#endif /* ifndef IO_PORT_H_ */
