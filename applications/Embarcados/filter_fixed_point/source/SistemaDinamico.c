#include "FreeRTOS.h"
#include "Task.h"

#include "Sistema.h"
#include "adc.h"
#include "dac.h"
#include "gpio_x.h"

void sistema (void *p){
	dacInit();
	adcInit();

	initSist();
	PORTB_CLK();
	PORTB_Mode(1, OUTPUT);
	PORTB_Write(1, LOW);
	
	TickType_t wakeTime = xTaskGetTickCount();
	uint16_t entrada;
	int16_t saida;
	while (1){
		vTaskDelayUntil(&wakeTime, getTs()*configTICK_RATE_HZ/1000);
				
		entrada = adcRead(PT_B0);
		
		PORTB_Write(1, HIGH);
		saida = equacaoDiff(entrada >> 4);
		PORTB_Write(1, LOW);
		
		dacWrite(saida);
	}
}

int main(void) {

	xTaskCreate(sistema, "sistema_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();

}
