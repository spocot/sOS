#include <stdio.h>

#include <kernel/tty.h>

static void prompt(void)
{
    printf(">");
}

/*static char *input(void)
{

}*/

int shell_run(void)
{
    while (1) {
        /*char *cmd;*/
        /*int proc;*/

        prompt();
        //cmd = input();
        //proc = process_start(cmd);
        //free(cmd);

        break;
    }

    return 0;
}

void kernel_main(void)
{
    /*int shell_return = 0;*/
    terminal_initialize();
    terminal_setfg(VGA_COLOR_CYAN);
    printf("Initializing Shell\n");
    terminal_setfg(VGA_COLOR_LIGHT_GREY);
    shell_run();
    printf("shell returned %d\nRestarting\n");
}
