/*
** DELOS PROJECT, 2025
** src/drivers/video/vga
** File description:
** VGA Source file
*/

#include "drivers/video/vga.h"

/**
 * @brief Variable vga_text_mmio is a pointer to the start of the VGA MMIO.
 *        Declared in src/drivers/video/vga.c
 */
unsigned char *vga_text_mmio = (unsigned char *) (VGA_TEXT_MODE_START_MMIO_ADDR);

/**
 * @brief Print a character on the screen at a certain coordinates using VGA.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
vga_putc_at(unsigned char x, unsigned char y, unsigned char c, unsigned char color)
{
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2)] = c;
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2) + 1] = color;
}
