#ifndef CONTROLLER_MANAGER
#define CONTROLLER_MANAGER
#include "Common.h"

void Controller_Manager_Init(uint8);
void Controller_Manager_MainFunction(void*);
void ControllerCallback(ps5_t, ps5_event_t);

#endif