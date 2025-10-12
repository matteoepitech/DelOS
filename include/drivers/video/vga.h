/*
** DELOS PROJECT, 2025
** include/drivers/video/vga
** File description:
** VGA Header file
*/

#ifndef DRIVER_VIDEO_VGA_H_
    #define DRIVER_VIDEO_VGA_H_

#ifndef VGA_TEXT_MODE_START_MMIO_ADDR
    #define VGA_TEXT_MODE_START_MMIO_ADDR 0xb8000
#endif /* ifndef VGA_TEXT_MODE_START_MMIO_ADDR */

/**
 * @brief Variable vga_text_mmio is a pointer to the start of the VGA MMIO.
 *        Declared in src/drivers/video/vga.c
 */
extern unsigned char *vga_text_mmio;

/**
 * @brief Print a character on the screen at a certain coordinates using VGA.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void vga_putc_at(unsigned char x, unsigned char y, unsigned char c, unsigned char color);

#endif /* ifndef DRIVER_VIDEO_VGA_H_ */
