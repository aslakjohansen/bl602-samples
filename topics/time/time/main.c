#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <bl_uart.h>
#include "bl_gpio.h"
#include "system.h"

#define DELAY (100)
#define PIN (14)

void TaskTime(void *pvParameters)
{
    while (1) {
        uint32_t tick_now;
        tick_now = *(volatile uint32_t*)0x0200BFF8;
        printf("%u\n", tick_now);
    }
}

void TaskBlink(void *pvParameters)
{
    bl_gpio_enable_output(PIN, 0, 0);
    while (1) {
        bl_gpio_output_set(PIN, 1);
        vTaskDelay(DELAY);
        bl_gpio_output_set(PIN, 0);
        vTaskDelay(DELAY);
    }
}

void bfl_main(void)
{
    system_init();
    bl_uart_init(0, 16, 7, 255, 255, 9600);
    printf("booted\n");
    xTaskCreate(TaskBlink, "Blink", 1024, NULL, 1, NULL);
    xTaskCreate(TaskTime, "Time", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
}

