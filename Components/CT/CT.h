#ifndef CT_H
#define CT_H
#include "Common.h"
#include "CT_RWI.h"

void CT_InitFunction(void*);
void CT_MainFunction(void*);

void WriteVar(Vars_enum id, void * value);
void* ReadVar(Vars_enum id);

#endif