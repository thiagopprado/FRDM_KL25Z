#include "fsl_device_registers.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "gpio_x.h"

#include "button.h"
#include "ledState.h"

xSemaphoreHandle xSemaphore = 0;

void blink_task (void *parameters){
	PORTB_CLK(); //Ativa o clock gate em PORTB
	PORTB_Mode(18, OUTPUT);
	PORTB_Mode(19, OUTPUT);
	PORTD_CLK();
	PORTD_Mode(1, OUTPUT); //Configura os LEDs vermelho, verde e azul

	PORTB_Write(18, HIGH); //Desliga os LEDs anodo comum
	PORTB_Write(19, HIGH); //Ativos por Zero
	PORTD_Write(1, HIGH);
	uint8_t portAtual = 18;

	while(1){
		if(xSemaphoreTake(xSemaphore, (500*configTICK_RATE_HZ)/1000)){ //Espera por 500ms
			switch (getState()){
			case 0:
				xSemaphoreGive(xSemaphore);
				portAtual = 18;
			break;
			case 1:
				xSemaphoreGive(xSemaphore);
				portAtual = 19;
			break;
			case 2:
				xSemaphoreGive(xSemaphore);
				portAtual = 1;
			break;
			default:
				setState(0);
				xSemaphoreGive(xSemaphore);
				portAtual = 18;
			break;
			}
		}
		if (portAtual == 1){
			PORTD_Write(portAtual, LOW); //Acende
		}
		else{
			PORTB_Write(portAtual, LOW);
		}

		vTaskDelay(500*configTICK_RATE_HZ/1000); //500 ms

		if (portAtual == 1){
			PORTD_Write(portAtual, HIGH); //Apaga
		}
		else{
			PORTB_Write(portAtual, HIGH);
		}

		vTaskDelay(500*configTICK_RATE_HZ/1000); //500 ms
	}
}

void button_task (void *parameters){
	bInit();
	uint8_t anterior = 0, atual = 0;
	while(1){
		bDebounce();
		anterior = atual;
		atual = bRead();
		if (atual == 1 && anterior == 0){ //botao foi pressionado
			if(xSemaphoreTake(xSemaphore, portMAX_DELAY)){ //Espera indefinidamente
				setState((getState() + 1)%3);//Incrementa e garante que seja < 3
				xSemaphoreGive(xSemaphore);
			}
		}

	}
}
int main(void){
	xSemaphore = xSemaphoreCreateMutex();

	xTaskCreate(blink_task, "blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(button_task, "button", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

	//Should never reach here
    for (;;);
    return 0;
}
