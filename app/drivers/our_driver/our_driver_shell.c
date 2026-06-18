# include <zephyr/shell/shell.h>

// shell subcommand handler defintion
static int cmd_channel_get_handler(const struct shell *sh , int argc , char ** argv)
{
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(channel_get, NULL, " Get channel of my /our_driver ", cmd_channel_get_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(our_driver_shellcmd, &our_driver_subcmd, "Our driver shell command", "NULL");