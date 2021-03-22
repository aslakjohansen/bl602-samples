#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <bl_uart.h>
#include "bl_gpio.h"
#include "system.h"
#include <bl_rtc.h>

#define DELAY (100)

void TaskCount(void *pvParameters)
{
    uint32_t i=0;
    
    while (1) {
        printf("%u", i%10);
        i++;
        vTaskDelay(DELAY);
    }
}

void bfl_main(void)
{
    system_init();
    bl_uart_init(0, 16, 7, 255, 255, 9600);
    printf("booted\n");
    xTaskCreate(TaskCount, "Count", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
}

