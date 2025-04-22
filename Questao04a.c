#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_adc_cal.h"

// Pinos do LED RGB
#define RED_PIN     32   // Pino do Vermelho
#define GREEN_PIN   33   // Pino do Verde
#define BLUE_PIN    25   // Pino do Azul

// Pinos dos Potenciômetros
#define RED_POT_PIN     ADC1_CHANNEL_0  // GPIO34 = ADC1_CHANNEL_6
#define GREEN_POT_PIN   ADC1_CHANNEL_3  // GPIO35 = ADC1_CHANNEL_7
#define BLUE_POT_PIN    ADC1_CHANNEL_6  // GPIO36 = ADC1_CHANNEL_6

void app_main(void)
{
    // === CONFIGURAÇÃO PWM (LED RGB) ===
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT, // 10 bits = 0 a 1023
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    // Configuração dos canais de PWM para cada cor (R, G, B)
    ledc_channel_config_t red_channel = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = RED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&red_channel);

    ledc_channel_config_t green_channel = {
        .channel    = LEDC_CHANNEL_1,
        .duty       = 0,
        .gpio_num   = GREEN_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&green_channel);

    ledc_channel_config_t blue_channel = {
        .channel    = LEDC_CHANNEL_2,
        .duty       = 0,
        .gpio_num   = BLUE_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&blue_channel);

    // === CONFIGURAÇÃO ADC (POTENCIÔMETROS) ===
    adc1_config_width(ADC_WIDTH_BIT_10); // 10 bits: 0-1023
    adc1_config_channel_atten(RED_POT_PIN, ADC_ATTEN_DB_12);   // Melhor faixa para 0-3.3V
    adc1_config_channel_atten(GREEN_POT_PIN, ADC_ATTEN_DB_12);
    adc1_config_channel_atten(BLUE_POT_PIN, ADC_ATTEN_DB_12);

    while (1) {
        // Lê os valores dos potenciômetros (0 a 1023)
        int red_value = adc1_get_raw(RED_POT_PIN);
        int green_value = adc1_get_raw(GREEN_POT_PIN);
        int blue_value = adc1_get_raw(BLUE_POT_PIN);

        // Define os duty cycles para as cores do LED
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, red_value);   // Vermelho
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, green_value); // Verde
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, blue_value);  // Azul

        // Atualiza os valores do PWM
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);

        // Apenas para debug (opcional)
        printf("Red: %d, Green: %d, Blue: %d\n", red_value, green_value, blue_value);

        // Delay para leitura estável
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
