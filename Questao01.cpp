#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "portmacro.h"

#define LED_PIN_1 2
#define LED_PIN_2 18
int i = 0;
int o = 0;

void app_main(void)
{
	gpio_reset_pin(LED_PIN_1);
	gpio_set_direction(LED_PIN_1,GPIO_MODE_OUTPUT);
	
	gpio_reset_pin(LED_PIN_2);
	gpio_set_direction(LED_PIN_2,GPIO_MODE_OUTPUT);
	
   	while(i<5){
		   	gpio_set_level(LED_PIN_1,1);
			vTaskDelay(50/portTICK_PERIOD_MS);
			gpio_set_level(LED_PIN_1,0);
			vTaskDelay(50/portTICK_PERIOD_MS);
			printf("value1: %d\n",i+1);
			i++;
	}
	while(o<3){
		   	gpio_set_level(LED_PIN_2,1);
			vTaskDelay(1000/(6 * portTICK_PERIOD_MS));
			gpio_set_level(LED_PIN_2,0);
			vTaskDelay(1000/(6 * portTICK_PERIOD_MS));
			printf("value2: %d\n",o+1);
			o++;
	}	
}
