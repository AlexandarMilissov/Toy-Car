idf_component_register(SRCS "Controller_Manager.c"
                       INCLUDE_DIRS "."
                       REQUIRES 
                       Common
                       Com
                       ps5-esp32
                       ps4-esp32
                       ps3-esp32
                       Bluetooth_Manager
                       )