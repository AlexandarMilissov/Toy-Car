#include "DCDriver.h"
#include "Common.h"
#include <stdio.h>
#include "driver/gpio.h"
#include "driver/dac.h"


gpio_num_t pin1 = GPIO_NUM_0;
gpio_num_t pinPWM = GPIO_NUM_0;
gpio_num_t pin2 = GPIO_NUM_0;

void SetPinoutDC(gpio_num_t newpin1, gpio_num_t newpinPWM, gpio_num_t newpin2)
{
    gpio_set_direction(pin1,GPIO_MODE_INPUT);
    gpio_set_direction(pinPWM,GPIO_MODE_INPUT);
    gpio_set_direction(pin2,GPIO_MODE_INPUT);

    pin1 = newpin1;
    pinPWM = newpinPWM;
    pin2 = newpin2;
    
    gpio_pad_select_gpio(pin1);
    gpio_pad_select_gpio(pinPWM);
    gpio_pad_select_gpio(pin2);

    gpio_set_direction(pin1,GPIO_MODE_OUTPUT);
    gpio_set_direction(pinPWM,GPIO_MODE_OUTPUT);
    gpio_set_direction(pin2,GPIO_MODE_OUTPUT);
}

void DCMove(uint8 speed, DCDirection direction)
{
    dac_output_enable(DAC_CHANNEL_1);
    dac_output_voltage(DAC_CHANNEL_1, speed);
    
    if(direction == STOPPED || speed == 0)
    {
        gpio_set_level(pin1 ,LOW);
        gpio_set_level(pin2, LOW);
        return;
    }
    else if(FORWARD == direction)
    {
        gpio_set_level(pin1, LOW);
        gpio_set_level(pin2, HIGH);
    }
    else if(BACKWARD == direction)
    {
        gpio_set_level(pin1,HIGH);
        gpio_set_level(pin1,LOW);
    }
}