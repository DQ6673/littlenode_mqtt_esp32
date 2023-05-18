#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "user_iic.h"
#include "wifi_connect.h"
#include "mqtt_app.h"
#include "sht20_app.h"
#include "led_app.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    sht20_app_start();

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    led_app_start();
    wifi_init_sta();

    mqtt_app_start();
}
