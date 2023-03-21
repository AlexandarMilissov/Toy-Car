idf_component_register(SRCS "MCM.c"
                       INCLUDE_DIRS "."
                       REQUIRES 
                       Common
                       Com
                       DriverM
                       esp_timer
                       CT
                       Logger
                       nvs_flash
                       )