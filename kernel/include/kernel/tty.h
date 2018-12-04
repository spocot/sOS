#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H 1

#include <stddef.h>
#include <stdint.h>

void terminal_clear(void);
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void terminal_change_colorat(uint8_t color, size_t x, size_t y);
uint8_t terminal_colorat(size_t x, size_t y);

#endif
