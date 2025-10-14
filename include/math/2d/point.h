/*
** EPITECH PROJECT, 2025
** include/math/2d/point
** File description:
** Math point header file
*/

#include "types.h"

#ifndef MATH_2D_POINT_H_
    #define MATH_2D_POINT_H_

/**
 * @brief A point structure containing 32 bits coordinates.
 *        -x = The X coordinate
 *        -y = The Y coordinate
 */
typedef struct point32_s {
    int32_t _x;
    int32_t _y;
} point32_t;

/**
 * @brief A point structure containing 8 bits coordinates.
 *        -x = The X coordinate
 *        -y = The Y coordinate
 */
typedef struct point8_s {
    int8_t _x;
    int8_t _y;
} point8_t;

#endif /* ifndef MATH_2D_POINT_H_ */
