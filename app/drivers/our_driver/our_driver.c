#include <zephyr/device.h>
#include <zephyr/logging/log_core.h>
#include <stdint.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include "../../src/sensor_custom.h"


#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);


// defining the data struct for the device having - our_driver compat
struct our_driver_data {
    int param;
};

// custom api implementaion wrapped on the standard available api of sensor.h  for l6-task1
static  int  channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val)
{
    LOG_INF("Hello from Channel Get, channel %d", chan);
    return 0;
}

// custom api implementation  wrapped on the standard available api of sensor.h  for l6-task1
static  int  sample_fetch_my_impl(const struct device *dev,
				    enum sensor_channel chan)
{

    LOG_INF("Hello from sample fetch" );
    return 0;

}

//custom data change API Implementaion
int custom_data_set_impl(const struct device *dev, int val)
{
  struct our_driver_data *dat = (struct our_driver_data *)dev->data;

  if(!dat){
    return -EINVAL;
  }
  dat->param = val;  
  return 0;
}


/*  
    wrapping the sensor subsystem api into implemented 
    our_driver API struct implementation which is "api_iomico_lecture"
    So DEVICE API is basically the function pointer struct for our_driver's implemented api instance - "api_iomico_lecture"
    Inside this function pointer struct we point to our modified implemented api (i.e channel_get_my_imp)
*/
static DEVICE_API(sensor, api_iomico_lecture) = {
        .channel_get = channel_get_my_impl,
        .sample_fetch = sample_fetch_my_impl,
};

/*Link the extension function into your custom API structure*/
const struct sensor_custom_driver_api custom_api_function = {
    .data_set =  custom_data_set_impl,
};

// Init fn for our device object
static int init( const struct device* dev){
    LOG_INF("Device Initialization");
    return 0;
}

// Instantiate the device under the standard subsystem
#define MY_DRIVER_INIT(inst)                                               \
    static struct our_driver_data our_driver_data_##inst;                  \
    DEVICE_DT_INST_DEFINE(inst,                                            \
                          init,NULL,&our_driver_data_##inst, NULL, POST_KERNEL, 8 , &api_iomico_lecture);

DT_INST_FOREACH_STATUS_OKAY(MY_DRIVER_INIT)


// creating the device struct  object 
// DEVICE_DT_INST_DEFINE(0, init,NULL ,NULL, &our_driver_data_0, NULL, PRE_KERNEL_1, 80 , &api_iomico_lecture);
