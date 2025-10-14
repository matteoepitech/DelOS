/*
** DELOS PROJECT, 2025
** src/drivers/video/vga
** File description:
** VGA Source file
*/

#include "drivers/video/vga.h"

/**
 * @brief Variable vga_text_mmio is a pointer to the start of the VGA MMIO.
 */
static uint8_t *vga_text_mmio = (uint8_t *) (VGA_TEXT_MODE_START_MMIO_ADDR);

/**
 * @brief Print a character on the screen at a certain coordinates using VGA.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
kvga_putc_at(uint8_t x, uint8_t y, uint8_t c, uint8_t color)
{
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2)] = c;
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2) + 1] = color;
}
