#ifndef MCMC_CFG_H
#define MCMC_CFG_H

#include "Common.h"
#include "Com.h"
#include "DriverM.h"
#include "CT.h"
#include "Controller_Manager.h"

#define CORE_0 0
#define CORE_1 1

typedef struct Init_cfg_struct{
    const char* name;
    void (*InitFunction)(void*);
}Init_cfg_struct;


typedef struct Task_cfg_struct{
    const char* name;
    void (*MainFunction)(void*);
    uint16 period;
    uint8 core;
    uint32 stack_size;
}Task_cfg_struct;

Init_cfg_struct init_cfg[] =
{
    {"CT",CT_InitFunction},
    {"Com",Com_InitFunction},
    {"DriverM",DriverM_InitFunction}
};
#define Init_cfg_size sizeof(init_cfg)/sizeof(Init_cfg_struct)
Task_cfg_struct task_cfg[] =
{
    {"Controller_Manager", Controller_Manager_MainFunction, 500, CORE_1, 4096},
    {"DriverM",DriverM_MainFunction, 20, CORE_0, 4096},
    {"CT",CT_MainFunction, 100, CORE_0, 4096}
};
#define Task_cfg_size sizeof(task_cfg)/sizeof(Task_cfg_struct)


#endif