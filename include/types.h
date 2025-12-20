/*
** DELOS PROJECT, 2025
** include/types
** File description:
** Types header file
*/

#ifndef TYPES_H_
    #define TYPES_H_

/**
 * @brief Unsigned char (1 byte)
 */
typedef unsigned char uint8_t;

/**
 * @brief Char (1 byte)
 */
typedef char int8_t;

/**
 * @brief Integer (4 bytes)
 */
typedef int int32_t;

/**
 * @brief Unsigned integer (4 bytes)
 */
typedef unsigned int uint32_t;

/**
 * @brief Unsigned integer (8 bytes)
 */
typedef unsigned long long uint64_t;

/**
 * @brief Unsigned integer (4 bytes)
 */
typedef uint32_t size_t;

/**
 * @brief Short (2 bytes)
 */
typedef short int16_t;

/**
 * @brief Unsigned short (2 bytes)
 */
typedef unsigned short uint16_t;


/**
 * @brief Unsigned char (1 byte)
 *        This type is used specially in structures or in arrays to save memory.
 *        Prefer using bool32_t if you work in stack, functions, condition for alignement.
 */
typedef uint8_t bool8_t;

/**
 * @brief Unsigned integer (4 bytes)
 */
typedef uint32_t bool32_t;

#endif /* ifndef TYPES_H_ */
