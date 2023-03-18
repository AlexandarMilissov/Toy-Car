#ifndef DCDRIVER_H
#define DCDRIVER_H
#include "Common.h"
#include "driver/gpio.h"


typedef enum DCDirection
{
    STOPPED,
    FORWARD,
    BACKWARD
}DCDirection;

void SetPinoutDC(gpio_num_t, gpio_num_t, gpio_num_t);
void DCMove(uint8, DCDirection);

#endif