#include "zephyr/device.h"
#include "zephyr/logging/log_core.h"
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include "sensor_custom_api.h"


#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_date{
    uint32_t param;
};


// custom api wrapped on the standard available api of sensor.h  for l6-task1
static  int  channel_get_my_imp(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val)
{

    LOG_INF("Hello from Channel Get, channel %d", chan);
    return 0;
}
// custom api wrapped on the standard available api of sensor.h  for l6-task1
static  int  sample_fetch_my_imp(const struct device *dev,
				    enum sensor_channel chan)
{

    LOG_INF("Hello from sample fetch" );
    return 0;

}

//custom data change API
static int custom_api_devicedate(const struct device *dev, uint32_t val){
  struct our_driver_date *data = dev->data;
  data->param = val;  
};


/*  
    wrapping the sensor subsystem api into implemented 
    our_driver API struct implementation which is "api_iomico_lecture"
    So DEVICE API is basically the function pointer struct for our_driver's implemented api instance - "api_iomico_lecture"
    Inside this function pointer struct we point to our modified implemented api (i.e channel_get_my_imp)
*/
static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_imp,
    .sample_fetch = sample_fetch_my_imp,
};


// Init fn for our device object
static int init( const struct device* dev){
    LOG_INF("Device Initialization");
    return 0;
}

// creating the device struct  object 
DEVICE_DT_INST_DEFINE(0, init, NULL , NULL, NULL, POST_KERNEL, 80 , &api_iomico_lecture);
