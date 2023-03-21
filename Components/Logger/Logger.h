#ifndef LOG_H
#define LOG_H

#include "Common.h"

typedef enum LogPriority
{
    Info,
    Warning,
    Error,
    Debug,
    Disable
}LogPriority;
#define LogPriority_Size 4

void Log_InitFunction(void*);
void Log_MainFunction(void*);

void Log_String(LogPriority, const char*, const char *);

#endif