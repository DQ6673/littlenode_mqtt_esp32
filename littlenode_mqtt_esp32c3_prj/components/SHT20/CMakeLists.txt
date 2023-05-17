set(srcs "sht20_driver.c" "sht20_app.c")

set(includes ".")

set(requires    "user_iic"
                "mqtt_app"
                )


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )