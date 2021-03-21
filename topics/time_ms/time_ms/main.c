#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <bl_uart.h>
#include "bl_gpio.h"
#include "system.h"
#include <bl_rtc.h>

#define DELAY (100)
#define PIN (14)

void TaskTime(void *pvParameters)
{
    bl_rtc_init();
    while (1) {
        uint32_t now = bl_rtc_get_timestamp_ms();
        printf("%u\n", now);
    }
}

void bfl_main(void)
{
    system_init();
    bl_uart_init(0, 16, 7, 255, 255, 9600);
    printf("booted\n");
    xTaskCreate(TaskTime, "Time", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
}

