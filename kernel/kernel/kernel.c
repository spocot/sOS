#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
    int i = 0;
    terminal_initialize();
    printf("Hello World!\n");
    while (i < 10) {
        printf(">%d\n", i++);
    }
    terminal_scroll();
}
