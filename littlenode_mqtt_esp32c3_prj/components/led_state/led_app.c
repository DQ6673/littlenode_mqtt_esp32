#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "led_driver.h"
#include "led_app.h"

static const char *TAG = "sht20";

QueueHandle_t led_app_queue = NULL;
blink_state_t led_blink_state = DEFAULT;

TaskHandle_t task_led_blink_handle;
#define task_led_blink_stackdepth 1024 * 2
#define task_led_blink_priority 1

static void task_led_blink(void *Param)
{
    for (;;)
    {
        xQueueReceive(led_app_queue, &led_blink_state, 10 / portTICK_PERIOD_MS);
        switch (led_blink_state)
        {
        case DEFAULT:
            led_on();
            vTaskDelay(250 / portTICK_PERIOD_MS);
            led_off();
            vTaskDelay(250 / portTICK_PERIOD_MS);
            break;

        case MQTT_CONNECTED:
            led_off();
            vTaskDelay(250 / portTICK_PERIOD_MS);
            break;

        case MQTT_PUBLISHED:
            led_on();
            vTaskDelay(100 / portTICK_PERIOD_MS);
            led_off();
            led_blink_state = MQTT_CONNECTED;
            break;

        default:
            led_blink_state = DEFAULT;
            break;
        }
    }
}

void led_app_start(void)
{
    led_driver_init();
    led_app_queue = xQueueCreate(10, sizeof(led_blink_state));

    xTaskCreate(task_led_blink,
                "task_led_blink",
                task_led_blink_stackdepth,
                NULL,
                task_led_blink_priority,
                &task_led_blink_handle);
}
