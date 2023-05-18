set(srcs "led_driver.c" "led_app.c")

set(includes ".")

set(requires 
                "driver"
                )


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${includes}
                       REQUIRES ${requires}
                       )