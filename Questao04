#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 2
#define LED2 4
#define LED3 16
#define LED4 17

void app_main(void) {
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED4, GPIO_MODE_OUTPUT);

    int estado1 = 0, estado2 = 0, estado3 = 0, estado4 = 0;

    while (1) {
        int c = getchar();

        if (c != EOF) {
            switch (c) {
                case '1':
                    estado1 = !estado1;
                    gpio_set_level(LED1, estado1);
                    printf("LED1 %s\n", estado1 ? "ON" : "OFF");
                    break;
                case '2':
                    estado2 = !estado2;
                    gpio_set_level(LED2, estado2);
                    printf("LED2 %s\n", estado2 ? "ON" : "OFF");
                    break;
                case '3':
                    estado3 = !estado3;
                    gpio_set_level(LED3, estado3);
                    printf("LED3 %s\n", estado3 ? "ON" : "OFF");
                    break;
                case '4':
                    estado4 = !estado4;
                    gpio_set_level(LED4, estado4);
                    printf("LED4 %s\n", estado4 ? "ON" : "OFF");
                    break;
                case '\n':
                case '\r':
                    break;
                default:
                    printf("Comando desconhecido: %c\n", c);
                    break;
            }
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
