idf_component_register(SRCS "Bluetooth_Manager.c"
                       INCLUDE_DIRS "."
                       REQUIRES 
                       Common
                       bt
                       arduino-esp32
                       )