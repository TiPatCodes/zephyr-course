#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <stdio.h>
static int board_scratch_board_init(void)
{
    printf("Board Initialized \n");
    return 0;
}