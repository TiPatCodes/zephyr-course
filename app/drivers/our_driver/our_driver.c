#include "zephyr/device.h"
#include "zephyr/logging/log_core.h"
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

// custom api wrapped on the standard available api of sensor.h  
static  int  channel_get_my_imp(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val)
{

    LOG_INF("Hello from Channel Get, channel %d", chan);
    return 0;
}

// wrapping the sensor subsystem api into implemented 
//our_driver API implementation
static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_imp,
};


// Init fn for our device object
static int init( const struct device* dev){
    LOG_INF("Device Initialization");
    return 0;
}


// creating the device struct  object 
DEVICE_DT_INST_DEFINE(0, init, NULL , NULL, NULL, POST_KERNEL, 80 , &api_iomico_lecture);

