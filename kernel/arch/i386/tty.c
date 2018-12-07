#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

/**
 * Clear the terminal by filling it with spaces.
 */
void terminal_clear(void)
{
    uint16_t c = vga_entry(' ', terminal_color);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = c;
        }
    }
}

/**
 * Initialize the terminal with the default colors and clear it out.
 */
void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    terminal_clear();
}

/**
 * Return the current color at the given terminal spot.
 */
uint8_t terminal_colorat(size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    return (uint8_t)(terminal_buffer[index] >> 8);
}

/**
 * Change the current terminal color.
 */
void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

/**
 * Scroll the terminal one line up.
 */
void terminal_scroll(void)
{
    size_t i;
    for (i = 0; i < VGA_HEIGHT - 1; i++) {
        memcpy(
                terminal_buffer + (i * VGA_WIDTH),
                terminal_buffer + ((i + 1) * VGA_WIDTH),
                VGA_WIDTH * sizeof(uint16_t)
              );
    }
    uint16_t empty_entry = vga_entry(' ', terminal_color);
    for (i = 0; i < VGA_WIDTH; i++) {
        const size_t index = ((VGA_HEIGHT - 1) * VGA_WIDTH) + i;
        terminal_buffer[index] = empty_entry;
    }
}

/**
 * Scroll the terminal X lines.
 */
void terminal_scrollnum(size_t num_lines)
{
    size_t i;
    for (i = 0; i < num_lines; i++) {
        terminal_scroll();
    }
}

void terminal_putchar(char c)
{
    unsigned char uc = c;
    if (uc == '\n') {
        terminal_column = 0;
        if (terminal_row == VGA_HEIGHT - 1) {
            terminal_scroll();
        } else {
            ++terminal_row;
        }
        return;
    }
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (terminal_row == VGA_HEIGHT - 1) {
            terminal_scroll();
        } else {
            ++terminal_row;
        }
    }
}

/**
 * Write <size> chars from <data> to the terminal.
 */
void terminal_write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

/**
 * Write the string <data> to the terminal.
 */
void terminal_writestring(const char *data)
{
    terminal_write(data, strlen(data));
}

/**
 * Change the color of the character at the specified position.
 */
void terminal_change_colorat(uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    unsigned char uc = terminal_buffer[index] & ((1 << 8) - 1);
    terminal_buffer[index] = vga_entry(uc, color);
}
