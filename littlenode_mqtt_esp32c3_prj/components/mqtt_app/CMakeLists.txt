set(srcs "mqtt_app.c")

set(includes ".")

set(requires 
                "wifi_connect"
                "mqtt"
                "sht20"
                "led_state"
                )


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )