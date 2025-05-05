#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/uart.h"

#define TAG "LED_SERIAL_CONTROL"

#define LED1 GPIO_NUM_2
#define LED2 GPIO_NUM_4
#define LED3 GPIO_NUM_16
#define LED4 GPIO_NUM_17

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024

int led_states[4] = {0, 0, 0, 0};

void app_main(void) {
    // Inicializa os GPIOs dos LEDs
    gpio_reset_pin(LED1);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_reset_pin(LED2);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_reset_pin(LED3);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_reset_pin(LED4);
    gpio_set_direction(LED4, GPIO_MODE_OUTPUT);

    // Configuração da UART
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);

    uint8_t data[BUF_SIZE];

    while (1) {
        int len = uart_read_bytes(UART_NUM, data, 1, pdMS_TO_TICKS(100));
        if (len > 0) {
            char command = data[0];
            switch (command) {
                case '1':
                    led_states[0] ^= 1;
                    gpio_set_level(LED1, led_states[0]);
                    ESP_LOGI(TAG, "LED 1 -> %d", led_states[0]);
                    break;
                case '2':
                    led_states[1] ^= 1;
                    gpio_set_level(LED2, led_states[1]);
                    ESP_LOGI(TAG, "LED 2 -> %d", led_states[1]);
                    break;
                case '3':
                    led_states[2] ^= 1;
                    gpio_set_level(LED3, led_states[2]);
                    ESP_LOGI(TAG, "LED 3 -> %d", led_states[2]);
                    break;
                case '4':
                    led_states[3] ^= 1;
                    gpio_set_level(LED4, led_states[3]);
                    ESP_LOGI(TAG, "LED 4 -> %d", led_states[3]);
                    break;
                default:
                    uart_write_bytes(UART_NUM, "Comando Desconhecido\n", strlen("Comando Desconhecido\n"));
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // pequena pausa para evitar uso excessivo da CPU
    }
}
