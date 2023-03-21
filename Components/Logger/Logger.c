#include "Logger.h"
#include "Common.h"
#include "Com.h"

#include <stdio.h>
#include <string.h>

#define LogStackMaxSize 512

struct loggerLevel
{
    Mutex lock; 
    uint32 length;
    char value[LogStackMaxSize];
};

void Log_Append(struct loggerLevel*, const char*);

LogPriority log_level;
struct loggerLevel Loggers[LogPriority_Size];

void Log_InitFunction(void* pvParameters)
{
    log_level = Error;
    for (size_t i = 0; i < LogPriority_Size; i++)
    {
        Loggers[i].length = 0;
        Loggers[i].lock = CreateMutex(); 
    }
}

void Log_MainFunction(void* pvParameters)
{
    for (size_t i = log_level; i < LogPriority_Size; i++)
    {
        if(Loggers[i].length <= 0)
        {
            continue;
        }
        LockMutex(Loggers[i].lock);

        printf("==== Log Level %d ====\n", i);
        printf("%s", Loggers[i].value);
        
        Loggers[i].value[0] = '\0';
        Loggers[i].length = 0;
        UnlockMutex(Loggers[i].lock);
    }
}

void Log_String(LogPriority priority, const char* value, const char * sender)
{
    if(log_level > priority)
    {
        return;
    }


    size_t valueLength = strlen(value);
    size_t senderLength = strlen(sender);
    size_t totalLength = Loggers[priority].length + valueLength + senderLength + 3;

    if(totalLength >= LogStackMaxSize)
    {
        return;
    }

    LockMutex(Loggers[priority].lock);

    Log_Append(&Loggers[priority], sender);
    Log_Append(&Loggers[priority], ": ");
    Log_Append(&Loggers[priority], value);
    Log_Append(&Loggers[priority], "\n");


    Loggers[priority].length += totalLength;

    UnlockMutex(Loggers[priority].lock);

    if(Error == priority)
    {
        Com_Feedback_Error();
    }
}

void Log_Append(struct loggerLevel* logger, const char* src)
{
    strcat(logger->value, src);
}