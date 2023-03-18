#include "DriverM.h"
#include "Common.h"
#include "CT_RWI.h"
#include "DCDriver.h"
#include "ServoDriver.h"
#include <stdio.h>

#define DC_PIN1 GPIO_NUM_0
#define DC_PINPWM GPIO_NUM_25
#define DC_PIN2 GPIO_NUM_2
#define SERVO_PIN GPIO_NUM_26

void DriverM_InitFunction(void* pvParameters)
{
    SetPinoutDC(DC_PIN1, DC_PINPWM, DC_PIN2);
    SetPinoutServo(SERVO_PIN);
}

void DriverM_MainFunction(void* pvParameters)
{
    //DriveDC();
    DriveServo();
    return;
}

void DriveDC()
{
    static sint8 forwardValue = 0;
    DCDirection directionX = STOPPED;

    forwardValue = Read_PointDirectionX();
    if(forwardValue > 0)
    {
        directionX = FORWARD;
    }
    else if (forwardValue < 0)
    {
        directionX = BACKWARD;
        forwardValue *= -1;
    }
    DCMove(forwardValue * 2, directionX);
}

void DriveServo()
{
    static sint8 sideValue = 0;
    ServoDirection directionY = RIGHT;

    sideValue = Read_PointDirectionY();
    
    if(sideValue < 0)
    {
        directionY = LEFT;
        sideValue += 1;
        sideValue *= -1;
    }
    else
    {
        directionY = RIGHT;
    }
    ServoMove(sideValue * 2, directionY);
}
