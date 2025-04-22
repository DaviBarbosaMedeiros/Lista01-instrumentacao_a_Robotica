#include <stdio.h>

// Inclusões do FreeRTOS
#include "driver/gpio.h"
#include "esp_err.h"               // Para manipulação de erros no ESP32
#include "freertos/FreeRTOS.h"     // Biblioteca principal do FreeRTOS
#include "freertos/projdefs.h"     // Definições de projeto do FreeRTOS
#include "freertos/task.h"         // Funções de tarefas (tasks) do FreeRTOS

// Inclusões do ADC (Conversor Analógico-Digital)
#include "esp_adc/adc_oneshot.h"   // Driver para leitura única do ADC

// Inclusões para logs (registro de mensagens)
#include "esp_log.h"               // Biblioteca de logs do ESP32
#include "hal/adc_types.h"         // Tipos de dados do ADC

#define LED_PIN_1 26
#define LED_PIN_2 25
#define LED_PIN_3 33
#define LED_PIN_4 32

const static char* TAG = "ADC Test"; // Tag para identificação nos logs
int adc_raw;                        // Variável para armazenar o valor bruto do ADC
int voltage;                        // Variável para armazenar a tensão calculada


// Função principal (entry point do programa)
void app_main(void)
{
	gpio_reset_pin(LED_PIN_1);
    gpio_set_direction(LED_PIN_1, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(LED_PIN_2);
    gpio_set_direction(LED_PIN_2, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(LED_PIN_3);
    gpio_set_direction(LED_PIN_3, GPIO_MODE_OUTPUT);
    
    gpio_reset_pin(LED_PIN_4);
    gpio_set_direction(LED_PIN_4, GPIO_MODE_OUTPUT);
    
    // Handle (manipulador) para a unidade ADC1
    adc_oneshot_unit_handle_t adc1_handle;

    // Configuração inicial da unidade ADC1
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,      // Usando o ADC1 (no ESP32, ADC_UNIT_1 refere-se ao ADC1)
    };

    // Inicializa a unidade ADC1 e verifica erros
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
    
    // Configuração do canal do ADC
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_10,  // Resolução padrão (10 bits no ESP32)
        .atten = ADC_ATTEN_DB_12,            // Atenuação de 0dB (faixa de tensão: ~0-800mV)
    };

    // Configura o canal 0 do ADC1 com as configurações definidas
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config));

    // Loop infinito para leitura contínua do ADC
    while(1) {
        // Lê o valor bruto do ADC no canal 0 e armazena em 'adc_raw'
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &adc_raw));
        
        // Log do valor bruto lido (0-4095 para 12 bits)
        ESP_LOGI(TAG, "ADC%d Channel[%d] Raw data: %d", ADC_UNIT_1 + 1, ADC_CHANNEL_0, adc_raw);
        
	    if (adc_raw < 128) {
		    gpio_set_level(LED_PIN_1, 0);
		    gpio_set_level(LED_PIN_2, 0);
		    gpio_set_level(LED_PIN_3, 0);
			gpio_set_level(LED_PIN_4, 0);
		} else if (adc_raw < 256) {
		    gpio_set_level(LED_PIN_1, 1);
		    gpio_set_level(LED_PIN_2, 0);
		    gpio_set_level(LED_PIN_3, 0);
		    gpio_set_level(LED_PIN_4, 0);
		} else if (adc_raw < 384) {
		    gpio_set_level(LED_PIN_1, 1);
		    gpio_set_level(LED_PIN_2, 1);
		    gpio_set_level(LED_PIN_3, 0);
		    gpio_set_level(LED_PIN_4, 0);
		} else if (adc_raw < 512) {
		    gpio_set_level(LED_PIN_1, 1);
		    gpio_set_level(LED_PIN_2, 1);
		    gpio_set_level(LED_PIN_3, 1);
		    gpio_set_level(LED_PIN_4, 0);
		} else {
		    gpio_set_level(LED_PIN_1, 1);
		    gpio_set_level(LED_PIN_2, 1);
		    gpio_set_level(LED_PIN_3, 1);
		    gpio_set_level(LED_PIN_4, 1);
		}

        
        // Delay de 1 segundo (1000 ms) usando FreeRTOS
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
