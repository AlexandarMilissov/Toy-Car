#ifndef COMMON_H
#define COMMON_H

#include "esp_task_wdt.h"
#include "stdint.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define PrintOut
//#undef PrintOut

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t   sint8;
typedef int16_t  sint16;
typedef int32_t  sint32;

#define TaskSleepMiliSeconds(value) vTaskDelay(value / portTICK_PERIOD_MS)
#define TaskSleepMicroSeconds(value) TaskSleepMiliSeconds(value / 1000)

#define Map(in, range_to_low, range_to_high, range_from_low, range_from_high) ((in-range_from_low)/(range_from_high-range_from_low) * (range_to_high - range_to_low) + range_to_low)

#ifndef LOW
    #define LOW 0x0
#endif

#ifndef HIGH
    #define HIGH 0x1
#endif

#endif