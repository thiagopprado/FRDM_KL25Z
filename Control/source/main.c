#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "gpio.h"
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "fsl_device_registers.h"
#include "MKL25Z4.h"
#include "pwm.h"
#include "controlador.h"

void mainTask(void *p){
	adcInit();

	pwmInit(TEMP1, CLK_MCG, 0xFFF, CMOD0, 0, ALIGN_EDGE);
	pwmInit(TEMP2, CLK_MCG, 0xFFF, CMOD0, 0, ALIGN_EDGE);

	pwmPortInit(TEMP1, 1, PRTB, 1); //PWM na PRTB1
	pwmDutyCicle(TEMP1, 1, 0);

	pwmPortInit(TEMP2, 0, PRTB, 2); //PWM na PRTB2
	pwmDutyCicle(TEMP2, 0, 0);


	PORTE_CLK();
	PORTE_Mode(30, OUTPUT);
	PORTE_Write(30, HIGH); //Enable

	uint16_t entrada = 0;
	int16_t saida = 0;

	initSist();

	uint8_t a;
	do{
		a = GETCHAR();
	}while (a == 0);

	TickType_t wakeTime = xTaskGetTickCount();
	for (;;){
		vTaskDelayUntil(&wakeTime, getTs()*configTICK_RATE_HZ/1000); //getTs em ms

		entrada = (adcRead(PT_B0) >> 4); //Reduz a resolução de 16 para 12 bits
		saida = equacaoDiff(entrada);
		int16_t controlSig;

		if (saida >= 0){
			controlSig = saida;
			saida = saida + 1500; //offset
			if (saida > 4095) //Saturação
				saida = 4095;

			pwmDutyCicle(TEMP1, 1, 0); //sentido positivo
			pwmDutyCicle(TEMP2, 0, saida);

		}
		else{
			saida = saida*(-1);
			controlSig = saida;
			saida = saida + 1500;
			if (saida > 4095)
				saida = 4095;

			pwmDutyCicle(TEMP2, 0, 0);
			pwmDutyCicle(TEMP1, 1, saida); //sentido negativo

			PUTCHAR('-');
		}

		PUTCHAR('0' + (controlSig/1000)%10);
		PUTCHAR('0' + (controlSig/100)%10);
		PUTCHAR('0' + (controlSig/10)%10);
		PUTCHAR('0' + controlSig%10);
		PUTCHAR(' ');

		PUTCHAR('0' + (entrada/1000)%10);
		PUTCHAR('0' + (entrada/100)%10);
		PUTCHAR('0' + (entrada/10)%10);
		PUTCHAR('0' + entrada%10);

		PUTCHAR('\r');
		PUTCHAR('\n');

	}

}

int main(void) {

  	// Init board hardware.
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	// Init FSL debug console.
    BOARD_InitDebugConsole();

    xTaskCreate(mainTask, "task_principal", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();

    return 0 ;
}
