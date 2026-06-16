#include "sensor_custom.h"
#include "sensor_custom_api.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>

#define SLEEP_TIME_MS CONFIG_APP_HEARTBEAT_PERIOD_MS

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    bool led_state = true;
    
    const struct device *my_dev = DEVICE_DT_GET(DT_NODELABEL(sensor);

    if (!device_is_ready(my_dev)) {
        return -ENODEV;
    }

    /* Safely invoke your custom API to modify instance state variables */
    int ret = custom_data_set(my_dev, 42);

    LOG_INF("Data value  : %d", my_dev->data->param);

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}