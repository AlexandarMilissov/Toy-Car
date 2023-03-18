#include "MCM.h"
#include "MCM_cfg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "Common.h"
#include "nvs_flash.h"

void Task(void*);

void MCM_Init(void)
{
    nvs_flash_init();

    for (size_t i = 0; i < Init_cfg_size; i++)
    {
        init_cfg[i].InitFunction(NULL);
    }

    for (size_t i = 0; i < Task_cfg_size; i++)
    {
        xTaskCreatePinnedToCore(Task,task_cfg[i].name,task_cfg[i].stack_size,&task_cfg[i],200,NULL,i%2);
    }
    
}

void Task(void *pvParameters)
{
    Task_cfg_struct cfg = *((Task_cfg_struct*)pvParameters);
    uint64 time = 0;
    esp_task_wdt_add(NULL);

    for(;;)
    {
        time = (esp_timer_get_time() / 1000);
        cfg.MainFunction(NULL);
        time = (esp_timer_get_time() / 1000) - time;
        esp_task_wdt_reset();
        if(cfg.period - time> 0)
        {
            TaskSleepMiliSeconds(cfg.period - time);
        }
        else
        {
            // task took more time to complete than it was its period
        }
    }

    vTaskDelete(NULL);
}