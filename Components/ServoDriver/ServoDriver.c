#include "ServoDriver.h"
#include "Common.h"
#include <stdio.h>
#include "iot_servo.h"


gpio_num_t pin = 0;

void SetPinoutServo(gpio_num_t newpin)
{
    pin = newpin;
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = 1000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = 32,
        .duty           = 0,
        .hpoint         = 0
    };
    servo_config_t servo_cfg =
    {
        .max_angle = MAX_LIB_ANGLE,
        .min_width_us = 500,
        .max_width_us = 2500,
        .freq = 50,
        .timer_number = LEDC_TIMER_0,
        .channels = {
            .servo_pin = {
                pin,
            },
            .ch = {
                LEDC_CHANNEL_0,
            },
        },
        .channel_number = 1,
    };
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, 0);
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
}

void ServoMove(uint8 value, ServoDirection dircetion)
{
    static float angle;
    // map the input value to a float value and add apply the direction to the float value
    angle = value;
    if(dircetion == LEFT)
    {
        angle *= -1;
    }

    angle = Map(angle, MIN_LIB_ANGLE, MAX_LIB_ANGLE, -UINT8_MAX, UINT8_MAX);
#ifdef PrintOut
    printf("Rotating at %.2f degrees\n",angle - MAX_LIB_ANGLE);
#endif

    // move the servo
    iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, angle);
}