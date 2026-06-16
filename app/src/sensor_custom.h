#ifndef  SENSOR_CUSTOM_H
#define  SENSOR_CUSTOM_H

#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

// typedef int (*custom_data_set_t) (const struct device *dev, int val);

// _subsystem  struct sensor_custom_driver_api{
// 	custom_data_set_t custome_data;
// };

// __syscall int custom_data_set(const struct device *dev,
// 			      int val);


// static inline int z_impl_custom_data_set(const struct device *dev, int val) {
//   const struct sensor_driver_api *api =
//       (const struct sensor_driver_api *)dev->api;

//   if (api->custome_data == NULL) {
//     return -ENOSYS;
//   }
//   return api->custome_data(dev, val);
// }


int custom_data_set(const struct device *dev,
			      int val);

#endif