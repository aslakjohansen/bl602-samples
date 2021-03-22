#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <bl_uart.h>
#include "bl_gpio.h"
#include "system.h"
#include <bl_rtc.h>
#include <bl_pwm.h>

#define DELAY (100)
#define PIN (0)
#define CHANNEL (0)
#define FREQUENCY (60000)

void TaskCount(void *pvParameters)
{
    printf("%u\n", bl_pwm_init(CHANNEL, PIN, FREQUENCY));
    printf("%u\n", bl_pwm_start(CHANNEL));
    while (1) {
        for (uint8_t i=0 ; i<=100 ; i++) {
            printf("%u > %u\n", i, bl_pwm_set_duty(CHANNEL, i));
            vTaskDelay(DELAY);
        }
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

