#include "CT.h"
#include "Common.h"

typedef struct Var_Wrapper{
    void* var;
    bool isSet;
}Var_Wrapper;

Var_Wrapper var_Wrappers[VARS_ENUM_SIZE];

void CT_InitFunction(void* pvParameters)
{
    for (size_t i = 0; i < VARS_ENUM_SIZE; i++)
    {
        var_Wrappers[i].var = 0;
        var_Wrappers[i].isSet = false;
    }
}

void CT_MainFunction(void* pvParameters)
{
    for (size_t i = 0; i < VARS_ENUM_SIZE; i++)
    {
        if(false == var_Wrappers[i].isSet)
        {
            var_Wrappers[i].var = 0;
            printf("CT Reset\n");
        }
        var_Wrappers[i].isSet = false;
    }
    return;
}

void WriteVar(Vars_enum id, void * value)
{
    var_Wrappers[id].var = value;
    var_Wrappers[id].isSet = true;
}

void* ReadVar(Vars_enum id)
{
    return var_Wrappers[id].var;
}