/*
** DELOS PROJECT, 2025
** src/drivers/video/vga
** File description:
** VGA Source file
*/

#include <utils/kstdlib/kmemory.h>
#include <utils/asm/io_port.h>
#include <drivers/video/vga.h>
#include <kernel/tty/tty.h>

/**
 * @brief Print a character on the screen at a certain coordinates using VGA.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
kvga_putc_at(uint8_t x, uint8_t y, char c, uint8_t color)
{
    if (x >= VGA_COLUMNS_MAX || y >= VGA_LINES_MAX) {
        return;
    }
    VGA_MMIO_ADDR[(y * VGA_COLUMNS_MAX * 2) + (x * 2)] = c;
    VGA_MMIO_ADDR[(y * VGA_COLUMNS_MAX * 2) + (x * 2) + 1] = color;
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
 * @brief Set the cursor visibility to hidden.
 *        0x0a -> manage the cursor visibility
 */
void
kvga_hide_cursor(void)
{
    outb(VGA_TEXT_MODE_CURSOR_REGISTER_ADDR, 0x0a);
    outb(VGA_TEXT_MODE_CURSOR_DATA_ADDR, 0x20);

}

/**
 * @brief Set the cursor visibility to visible.
 *        0x0a -> manage the cursor visibility
 */
void
kvga_show_cursor(void)
{
    outb(VGA_TEXT_MODE_CURSOR_REGISTER_ADDR, 0x0a);
    outb(VGA_TEXT_MODE_CURSOR_DATA_ADDR, (inb(VGA_TEXT_MODE_CURSOR_DATA_ADDR) & 0xC0) | 0);
    outb(VGA_TEXT_MODE_CURSOR_REGISTER_ADDR, 0x0b);
    outb(VGA_TEXT_MODE_CURSOR_DATA_ADDR, (inb(VGA_TEXT_MODE_CURSOR_DATA_ADDR) & 0xe0) | 15);
}

/**
 * @brief Do a scroll to the top. Using kmemmove.
 */
void
kvga_scroll_line(void)
{
    void *vm = (void *) VGA_MMIO_ADDR + (VGA_LINES_MAX * VGA_COLUMNS_MAX * 2) - (VGA_COLUMNS_MAX * 2);

    kmemmove(
        (void *) VGA_MMIO_ADDR,
        (void *) VGA_MMIO_ADDR + (VGA_COLUMNS_MAX * 2),
        (VGA_COLUMNS_MAX * VGA_LINES_MAX * 2) - (VGA_COLUMNS_MAX * 2)
    );
    kwmemset((uint16_t *) vm, (VGA_TEXT_DEFAULT_COLOR << 8) | ' ', VGA_COLUMNS_MAX);
}

/**
 * @brief Fill the VGA buffer to the c character and his color.
 *
 * @param c             The character
 * @param color         The color
 */
void
kvga_fill(char c, uint8_t color)
{
    kwmemset((void *) VGA_MMIO_ADDR, ((uint16_t) color << 8) | c, VGA_COLUMNS_MAX * VGA_LINES_MAX);
}

/**
 * @brief Print a character on the screen at a certain coordinates using physical VGA address.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param c             The character
 * @param color         The color
 */
void
kvga_phys_putc_at(uint8_t x, uint8_t y, char c, uint8_t color)
{
    if (x >= VGA_COLUMNS_MAX || y >= VGA_LINES_MAX) {
        return;
    }
    volatile uint8_t *vga_phys = (volatile uint8_t *) VGA_TEXT_MODE_START_MMIO_ADDR;
    vga_phys[(y * VGA_COLUMNS_MAX * 2) + (x * 2)] = c;
    vga_phys[(y * VGA_COLUMNS_MAX * 2) + (x * 2) + 1] = color;
}

/**
 * @brief Print a string on the screen at a certain coordinates using physical VGA address.
 *
 * @param x             The coordinate X
 * @param y             The coordinate Y
 * @param string        The string
 * @param color         The color
 */
void
kvga_phys_puts_at(uint8_t x, uint8_t y, const char *string, uint8_t color)
{
    if (string == NULL) {
        return;
    }
    volatile uint8_t *vga_phys = (volatile uint8_t *) VGA_TEXT_MODE_START_MMIO_ADDR;
    size_t len = 0;
    while (string[len] != '\0') {
        len++;
    }
    for (size_t i = 0; i < len; i++) {
        if (x + i >= VGA_COLUMNS_MAX) {
            break;
        }
        size_t pos = (y * VGA_COLUMNS_MAX * 2) + ((x + i) * 2);
        vga_phys[pos] = string[i];
        vga_phys[pos + 1] = color;
    }
}

/**
 * @brief Fill the VGA buffer using physical address.
 *
 * @param c             The character
 * @param color         The color
 */
void
kvga_phys_fill(char c, uint8_t color)
{
    volatile uint8_t *vga_phys = (volatile uint8_t *) VGA_TEXT_MODE_START_MMIO_ADDR;
    for (uint32_t i = 0; i < VGA_COLUMNS_MAX * VGA_LINES_MAX; i++) {
        vga_phys[i * 2] = c;
        vga_phys[i * 2 + 1] = color;
    }
}
