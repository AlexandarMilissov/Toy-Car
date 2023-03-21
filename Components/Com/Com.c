#include "Com.h"
#include "CT_RWI.h"
#include "Controller_Manager.h" 
#include <stdio.h>
#include "Common.h"

#define Default_Priority 0
#define Controller_Priority 10

void Com_InitFunction(void* pvParameters)
{
    Controller_Manager_Init(Controller_Priority);
}

void Input_Write_Target_Position(sint8 target_position_X, sint8 target_position_Y, uint8 senderID)
{
    static uint8 lastWritter;
    lastWritter = Read_PositionLastWriterID();

    if(senderID >= lastWritter)
    {
        Write_PositionLastWriterID(senderID);
        Write_PointDirectionX(target_position_X);
        Write_PointDirectionY(target_position_Y);
    }
}

void Com_Feedback_Error()
{
    Controller_Feedback_Error();
}