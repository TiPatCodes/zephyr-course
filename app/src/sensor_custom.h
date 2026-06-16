#ifndef SENSOR_CUSTOM_H_
#define SENSOR_CUSTOM_H_

#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

/*
To add a custom extension API to a Zephyr driver that already implements a standard subsystem,
you must define a custom API structure alongside your subsystem implementations, 
expose it via a public header file, and implement a wrapper function that extracts the device's internal data structure to mutate it
*/

/*
According to the official Zephyr Driver Model Documentation, drivers can support driver-specific extensions directly. 

Because your custom API is tied to your driver implementation and not part of the standard subsystem structure, 
you will bypass the standard const void *api pointer in struct device and invoke your custom driver functions directly by passing the device pointer.
OR
Because the driver is already bound to a standard subsystem (like sensor, GPIO, or I2C),
your extension bypasses the standard dev->api struct pointer and directly executes your custom implementation 
function while mutating your driver's runtime data pointer.
*/




typedef int (*custom_data_set_t) (const struct device *dev, int val);

struct sensor_custom_driver_api{
  custom_data_set_t data_set;

};

__syscall int custom_data_set(const struct device *dev,
			      int val);

// Define the public inline function called from main.c
static inline int custom_data_set(const struct device *dev, int val)
{
  /*Bypasssing the standard subsystem api structure reference*/
  // const struct sensor_custom_driver_api *api =
  //     (const struct sensor_custom_driver_api *)dev->api;

  extern const struct sensor_custom_driver_api custom_api_function;
  
  if (custom_api_function.data_set == NULL) {
    return -ENOSYS;
  }
  return custom_api_function.data_set(dev, val);
}



/* 
OPTION - 2
For implementing as a custom function 
*/

// int custom_data_set(const struct device *dev,
// 			      int val);

// #include <zephyr/syscalls/sensor_custom.h>

#endif
