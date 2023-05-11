set(srcs "app_main.c")

set(includes ".")

set(requires 
                "driver"
                "nvs_flash"
                "wifi_connect"    
                "SHT20"
                #"mqtt_app"
                "user_iic"
)

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )