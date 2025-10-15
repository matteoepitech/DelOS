/*
** DELOS PROJECT, 2025
** src/drivers/video/vga
** File description:
** VGA Source file
*/

#include "utils/kstdlib/kmemory.h"
#include "utils/asm/io_port.h"
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
    if (x >= VGA_COLUMNS_MAX || y >= VGA_LINES_MAX) {
        return;
    }
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2)] = c;
    vga_text_mmio[(x * 2) + (y * VGA_COLUMNS_MAX * 2) + 1] = color;
}

/**
 * @brief Refresh the cursor position using the new_position parameter.
 *
 * @param new_position          The new position
 */
void
kvga_set_cursor_position(point8_t new_position)
{
    uint16_t pos = new_position._y * VGA_COLUMNS_MAX + new_position._x;

    outb(VGA_TEXT_MODE_CURSOR_REGISTER_ADDR, 0x0e);
    outb(VGA_TEXT_MODE_CURSOR_DATA_ADDR, (pos & 0xff00) >> 8);
    outb(VGA_TEXT_MODE_CURSOR_REGISTER_ADDR, 0x0f);
    outb(VGA_TEXT_MODE_CURSOR_DATA_ADDR, pos & 0x00ff);
}

/**
 * @brief Do a scroll to the top. Using kmemmove.
 */
void
kvga_scroll_line(void)
{
    kmemmove(vga_text_mmio, vga_text_mmio + (VGA_COLUMNS_MAX * 2), ((VGA_COLUMNS_MAX * VGA_LINES_MAX * 2) - (VGA_COLUMNS_MAX * 2)));
    kmemset(vga_text_mmio + (VGA_COLUMNS_MAX * VGA_LINES_MAX * 2) - (VGA_COLUMNS_MAX * 2), 0, VGA_COLUMNS_MAX * 2);
}
