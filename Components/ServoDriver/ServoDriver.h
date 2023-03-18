#ifndef SERVODRIVER_H
#define SERVODRIVER_H
#include "Common.h"

#define MIN_LIB_ANGLE 0
#define MID_LIB_ANGLE (MIN_LIB_ANGLE + MAX_LIB_ANGLE)/2
#define MAX_LIB_ANGLE 180

#define MIN_REAL_ANGLE -90
#define MID_REAL_ANGLE (MIN_REAL_ANGLE + MAX_REAL_ANGLE)/2
#define MAX_REAL_ANGLE +90

typedef enum ServoDirection
{
    LEFT,
    RIGHT
}ServoDirection;

void SetPinoutServo(gpio_num_t);
void ServoMove(uint8, ServoDirection);

#endif