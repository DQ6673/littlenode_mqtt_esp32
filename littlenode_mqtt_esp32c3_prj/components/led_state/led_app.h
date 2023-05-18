#ifndef _LED_APP_H_
#define _LED_APP_H_

typedef enum
{
    DEFAULT = 0,
    MQTT_CONNECTED,
    MQTT_PUBLISHED,
} blink_state_t;

void led_app_start(void);

#endif