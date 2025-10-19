/*
** DELOS PROJECT, 2025
** include/utils/memory
** File description:
** Memory header file
*/

#include "types.h"

#ifndef UTILS_KSTDLIB_KMEMORY_H_
    #define UTILS_KSTDLIB_KMEMORY_H_

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
kmemset(void *addr, uint8_t byte, size_t len);

/**
 * @brief Kernel word memset.
 *        Put the 2 bytes values at the addr for len bytes.
 *
 * @param addr          The address to start the set
 * @param word          The word to set
 * @param len           The n times we do it
 *
 * @return addr
 */
void *
kwmemset(void *addr, uint16_t word, size_t len);

/**
 * @brief Kernel memcpy.
 *
 * @param dst           The address to start the copy
 * @param src           The address where to take data from
 * @param n             The n times we do it
 *
 * @return dst
 */
void *
kmemcpy(void *restrict dst, const void *restrict src, size_t n);

/**
 * @brief Kernel memmove.
 *
 * @param dst           The address to start the move
 * @param src           The address where to take data from
 * @param n             The n times we do it
 *
 * @return dst
 */
void *
kmemmove(void *dst, const void *src, size_t n);

#endif /* ifndef UTILS_KSTDLIB_KMEMORY_H_ */
