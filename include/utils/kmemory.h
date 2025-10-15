/*
** DELOS PROJECT, 2025
** include/utils/memory
** File description:
** Memory header file
*/

#include "types.h"

#ifndef UTILS_KMEMORY_H_
    #define UTILS_KMEMORY_H_

/**
 * @brief Kernel memset.
 *        Put the byte value at the addr for len bytes.
 *
 * @param addr          The address to start the set
 * @param byte          The byte to set
 * @param len           The n times we do it
 *
 * @return addr
 */
void *
kmemset(void *addr, int8_t byte, uint32_t len);

#endif /* ifndef UTILS_KMEMORY_H_ */
