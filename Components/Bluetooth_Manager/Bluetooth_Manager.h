#ifndef BLUETOOTH_MANAGER_H

void Bluetooth_Manager_Init(btInitMode);

typedef enum btInitMode
{
    btInitStateInitiator,
    btInitStateAcceptorController
} btInitMode;

#define BLUETOOTH_MANAGER_H
#endif