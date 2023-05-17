#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "sht20_driver.h"
#include "mqtt_app.h"
#include "sht20_app.h"

static const char *TAG = "sht20";

sht20_data_t sht20_data;
mqtt_app_queue_payload_t mqtt_payload_send;

extern QueueHandle_t mqtt_app_queue;

TaskHandle_t task_sht20_get_handle;
#define task_sht20_get_stackdepth 1024 * 2
#define task_sht20_get_priority 1

static void task_sht20_get(void *Param)
{
    mqtt_app_queue_payload_t *mqtt_send = &mqtt_payload_send;
    mqtt_send->app_name = "sht20";
    mqtt_send->payload = &sht20_data;

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    sht20_reset();
    vTaskDelay(20 / portTICK_PERIOD_MS);

    for (;;)
    {
        sht20_trigger_T();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        while (sht20_recive_T(&sht20_data.temp) != ESP_OK)
            vTaskDelay(10 / portTICK_PERIOD_MS);

        sht20_trigger_RH();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        while (sht20_recive_RH(&sht20_data.RH) != ESP_OK)
            vTaskDelay(10 / portTICK_PERIOD_MS);

        // ESP_LOGI(TAG, "tempreture is %.2fC, humidity is %.2f%%", sht20_data.temp, sht20_data.RH);

        sht20_reset();

        xQueueSend(mqtt_app_queue, &mqtt_send, 0);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void sht20_app_start(void)
{
    xTaskCreate(task_sht20_get,
                "task_sht20_get",
                task_sht20_get_stackdepth,
                NULL,
                task_sht20_get_priority,
                &task_sht20_get_handle);
}
