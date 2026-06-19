#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "../../src/sensor_custom.h"



// shell subcommand handler defintion
static int cmd_sample_fetch_handler(const struct shell *sh , int argc , char ** argv)
{
    const struct device * DriverDev = shell_device_get_binding(argv[1]);

    if (!device_is_ready(DriverDev)) {
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(DriverDev);
    if(!ret)
    {
        shell_fprintf(sh, SHELL_INFO ,"%s", "Sample didn't fetch\n");
    }
    shell_info(sh,"The device sample fetch is %d\n",ret);
    return 0;
}

static int cmd_channel_get_handler(const struct shell *sh , int argc , char ** argv)
{
    const struct device *DriverDev  = shell_device_get_binding(argv[1]);
    if (!device_is_ready(DriverDev)) {
        return -ENODEV;
    }
    struct sensor_value Value;

    int ret = sensor_channel_get(DriverDev, 0 , &Value);
    if(!ret)
    {
        shell_fprintf(sh, SHELL_INFO ,"%s", "Channel didn't get value\n");
    }

    shell_info(sh, "The Channel value is %d\n", Value.val1);

    return 0;
}

static int cmd_channel_info_handler(const struct shell *sh , int argc , char ** argv)
{
    const struct device *DriverDev  = shell_device_get_binding(argv[1]);
    if (!device_is_ready(DriverDev)) {
        return -ENODEV;
    }
    shell_info(sh,"The device name %s", DEVICE_DT_NAME(DT_INST(0,our_driver)));
    shell_info(sh,"The device state %d\n", device_is_ready(DriverDev));

    return 0;
}

//l7-task2
static int cmd_channel_set_handler(const struct shell *sh , int argc , char ** argv)
{
    const struct device *DriverDev  = shell_device_get_binding(argv[1]);
    if (!device_is_ready(DriverDev)) {
        return -ENODEV;
    }
    // shell_info(sh,"The device name %s", DEVICE_DT_NAME(DT_INST(0,our_driver)));
    // shell_info(sh,"The device state %d\n", device_is_ready(DriverDev));
    int ValSet =  (int)argv[2];
    
    int ret = custom_data_set(DriverDev,ValSet);
    if(!ret)
    {
        shell_fprintf(sh, SHELL_INFO ,"%s", "Channel didn't get value\n");
    }
    
    shell_info(sh, "The Channel value set was %d\n", ValSet);
  
    return 0;
}



// shell subcommnad set creation
SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD(fetch, NULL, " Get channel fetch our_driver", cmd_sample_fetch_handler),
    SHELL_CMD(read, NULL, " Get channel read our_driver", cmd_channel_get_handler),
    SHELL_CMD(info, NULL, " Prints the device name and ready state", cmd_channel_info_handler),
    SHELL_CMD_ARG(info, NULL, " Set the value to data struct of driver device", cmd_channel_set_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

//registering the subcommand 
SHELL_CMD_REGISTER(sensor, &our_driver_subcmd, "Our driver shell command", "NULL");