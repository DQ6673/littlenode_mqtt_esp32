#ifndef _MQTT_APP_H_
#define _MQTT_APP_H_

typedef struct
{
    char *app_name;
    void *payload;
} mqtt_app_queue_payload_t;

void mqtt_app_start(void);

#endif