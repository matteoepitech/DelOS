/*
** DELOS PROJECT, 2025
** include/drivers/video/vga
** File description:
** VGA Header file
*/

#include "types.h"
#include "math/2d/point.h"

#ifndef DRIVER_VIDEO_VGA_H_
    #define DRIVER_VIDEO_VGA_H_

#ifndef VGA_TEXT_MODE_START_MMIO_ADDR
    #define VGA_TEXT_MODE_START_MMIO_ADDR 0xb8000
#endif /* ifndef VGA_TEXT_MODE_START_MMIO_ADDR */

#ifndef VGA_TEXT_MODE_CURSOR_REGISTER_ADDR
    #define VGA_TEXT_MODE_CURSOR_REGISTER_ADDR 0x3d4
#endif /* ifndef VGA_TEXT_MODE_CURSOR_REGISTER_ADDR */

#ifndef VGA_TEXT_MODE_CURSOR_DATA_ADDR
    #define VGA_TEXT_MODE_CURSOR_DATA_ADDR 0x3d5
#endif /* ifndef VGA_TEXT_MODE_CURSOR_DATA_ADDR */

#ifndef VGA_COLUMNS_MAX
    #define VGA_COLUMNS_MAX 80
#endif /* ifndef VGA_COLUMNS_MAX */

#ifndef VGA_LINES_MAX
    #define VGA_LINES_MAX 25
#endif /* ifndef VGA_LINES_MAX */

#ifndef VGA_COLORS_VALUES_H_
    #define VGA_COLORS_VALUES_H_

    #define VGA_BLACK_FOREGROUND         0x00
    #define VGA_BLUE_FOREGROUND          0x01
    #define VGA_GREEN_FOREGROUND         0x02
    #define VGA_CYAN_FOREGROUND          0x03
    #define VGA_RED_FOREGROUND           0x04
    #define VGA_MAGENTA_FOREGROUND       0x05
    #define VGA_BROWN_FOREGROUND         0x06
    #define VGA_GRAY_FOREGROUND          0x07
    #define VGA_DARKGRAY_FOREGROUND      0x08
    #define VGA_BRIGHTBLUE_FOREGROUND    0x09
    #define VGA_BRIGHTGREEN_FOREGROUND   0x0A
    #define VGA_BRIGHTCYAN_FOREGROUND    0x0B
    #define VGA_BRIGHTRED_FOREGROUND     0x0C
    #define VGA_BRIGHTMAGENTA_FOREGROUND 0x0D
    #define VGA_YELLOW_FOREGROUND        0x0E
    #define VGA_WHITE_FOREGROUND         0x0F

    #define VGA_BLACK_BACKGROUND         0x00
    #define VGA_BLUE_BACKGROUND          0x10
    #define VGA_GREEN_BACKGROUND         0x20
    #define VGA_CYAN_BACKGROUND          0x30
    #define VGA_RED_BACKGROUND           0x40
    #define VGA_MAGENTA_BACKGROUND       0x50
    #define VGA_BROWN_BACKGROUND         0x60
    #define VGA_GRAY_BACKGROUND          0x70
    #define VGA_DARKGRAY_BACKGROUND      0x80
    #define VGA_BRIGHTBLUE_BACKGROUND    0x90
    #define VGA_BRIGHTGREEN_BACKGROUND   0xA0
    #define VGA_BRIGHTCYAN_BACKGROUND    0xB0
    #define VGA_BRIGHTRED_BACKGROUND     0xC0
    #define VGA_BRIGHTMAGENTA_BACKGROUND 0xD0
    #define VGA_YELLOW_BACKGROUND        0xE0
    #define VGA_WHITE_BACKGROUND         0xF0

    #define VGA_TEXT_DEFAULT_COLOR       VGA_WHITE_FOREGROUND | VGA_BLACK_BACKGROUND
    #define VGA_TEXT_ERROR_COLOR         VGA_RED_FOREGROUND | VGA_BLACK_BACKGROUND
#endif /* VGA_COLORS_VALUES_H_ */

/**
 * @brief Print a character on the screen at a certain coordinates using VGA.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
kvga_putc_at(uint8_t x, uint8_t y, uint8_t c, uint8_t color);

/**
 * @brief Refresh the cursor position using the new_position parameter.
 *
 * @param new_position          The new position
 */
void
kvga_set_cursor_position(point8_t new_position);

/**
 * @brief Do a scroll to the top. Using kmemmove.
 */
void
kvga_scroll_line(void);

#endif /* ifndef DRIVER_VIDEO_VGA_H_ */
