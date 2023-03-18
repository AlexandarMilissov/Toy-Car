idf_component_register(SRCS "DriverM.c"
                       INCLUDE_DIRS "."
                       REQUIRES
                       Common
                       CT
                       DCDriver
                       ServoDriver
                       )