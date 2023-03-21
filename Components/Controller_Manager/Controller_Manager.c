#include "Controller_Manager.h" 
#include "Common.h"
#include "Com.h"

#define PS_5
#include "PS_Controller_Wrapper.h"
#include "Bluetooth_Manager.h"

#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp32-hal-bt.h"

uint8 id = 0;
static sint8 posX = 0;
static sint8 posY = 0;

ps5_cmd_t ControllerFeedBack = 
{
  .smallRumble = 0,
  .largeRumble = 0,
  .r = 0,
  .g = 0,
  .b = 255,
  .flashOn = 0,
  .flashOff = 0
};
uint8 FlashErrorCounter = 0;

void LeftStick(sint8,sint8);

void Controller_Manager_Init(uint8 _id)
{
    id = _id;
    btInitMode btInitState = btInitStateAcceptorController;
    
    btStart();
    esp_bluedroid_init();
    esp_bluedroid_enable();
    
    psInit();
    psSetEventCallback(ControllerCallback);
    
    
    if (btInitStateInitiator == btInitState)
    {
        esp_bd_addr_t bt_5 = {0x7c,0x66,0xef,0x45,0x7e,0xe1};
        ps5_l2cap_connect(bt_5);
    }
}
void Controller_Manager_MainFunction(void * pvParameters)
{
    if(!ps5IsConnected())
    {
        return;
    }


    if(FlashErrorCounter != 0)
    {
        FlashErrorCounter--;
    }
    else
    {
        ControllerFeedBack.r = 255;
        ControllerFeedBack.g = 0;
        ControllerFeedBack.b = 0;
    }
    ps5SetOutput(ControllerFeedBack);
    
}

void ControllerCallback( ps_t ps, ps_event_t event )
{
    LeftStick(ps.analog.stick.ly, ps.analog.stick.lx);

    TaskSleepMiliSeconds(1);
}

void LeftStick(sint8 x, sint8 y)
{
    if(abs(x) + abs(y) > 10)
    {
        posX = x;
        posY = y;
        Input_Write_Target_Position(posX, posY, id);
    }
}
void Controller_Feedback_Error()
{
    ControllerFeedBack.r = 255;
    ControllerFeedBack.g = 0;
    ControllerFeedBack.b = 0;

    FlashErrorCounter = 2;
}