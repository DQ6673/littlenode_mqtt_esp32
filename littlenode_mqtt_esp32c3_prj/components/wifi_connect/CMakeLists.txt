set(srcs "wifi_connect.c")

set(includes ".")

set(requires 
                "esp_wifi"
                "nvs_flash"
                )


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )