#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
    int i = 0;
    terminal_initialize();
    printf("Hello World!\n");
    while (i < 1000) {
        printf(">%d\n", i++);
    }
    terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    printf("test\n");
}
