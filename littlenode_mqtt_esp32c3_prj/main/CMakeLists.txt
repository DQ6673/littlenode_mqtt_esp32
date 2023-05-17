set(srcs "app_main.c")

set(includes ".")

set(requires 
                "driver"
                "wifi_connect"    
                "sht20"
                "mqtt_app"
                "user_iic"
)

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )