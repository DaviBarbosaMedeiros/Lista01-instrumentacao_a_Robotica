
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LDR_CHANNEL     ADC1_CHANNEL_6   // GPIO34
#define LED_GPIO        2               // GPIO do LED
#define TAG             "LDR_LED_CONTROL"

#define MAX_ADC_VALUE   1023             // Resolução de 10 bits

void app_main(void)
{
    // Configura ADC
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(LDR_CHANNEL, ADC_ATTEN_DB_11);

    // Configura PWM com resolução de 10 bits (0 a 1023)
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_HIGH_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,  // 10 bits = 0–1023
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = LED_GPIO,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);

    while (1) {
        int ldr_value = adc1_get_raw(LDR_CHANNEL);
		int duty_value = abs(1023-ldr_value);
        // Usa o valor do LDR diretamente como duty cycle
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty_value);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);

        ESP_LOGI(TAG, "LDR: %d", ldr_value);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
