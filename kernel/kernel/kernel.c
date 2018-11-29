#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
    terminal_initialize();
    printf("Hello World!\n");
    printf("Line 2\n");
}
