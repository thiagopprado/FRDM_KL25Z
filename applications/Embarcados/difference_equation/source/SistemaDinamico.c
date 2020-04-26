#include "FreeRTOS.h"
#include "Task.h"

#include "Sistema.h"
#include "adc.h"
#include "dac.h"

void sistema (void *p){
	dacInit();
	adcInit();

	initSist();

	TickType_t wakeTime = xTaskGetTickCount();
	uint16_t entrada, saida;
	while (1){
		vTaskDelayUntil(&wakeTime, getTs()*configTICK_RATE_HZ/1000); //getTs em ms
		entrada = adcRead(PT_B0);
		saida = equacaoDiff(entrada >> 4); //Reduz a resolução de 16 para 12 bits
		dacWrite(saida); //12 bits
	}
}

int main(void) {

	xTaskCreate(sistema, "sistema_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();

}
