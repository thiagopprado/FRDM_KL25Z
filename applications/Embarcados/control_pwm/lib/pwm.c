#include "pwm.h"


/* Function: pwmInit
 *
 * Initializes the timer module, clock source, output
 * frequency, counting mode and signal alignment
 *
 * @param temp is the timer module = TEMP0, TEMP1 or TEMP2
 * @param clk is the clock source = CLK_MCG, CLK_OSCER or CLK_MCGIR
 * @param max is the maximum value of the counter. If pwmDutyCicle.value > max then DutyCicle = 100% (16 bits)
 * @param cmod is the counting mode = CMOD0 (every clock) or CMOD1 (external clock)
 * @param prescaler is the value with wich the core frequency will be divided to feed the timer (2^prescaler)
 * 		pwm frequency = f_core/(max*(2^prescaler))
 * @param align is the signal alignment = ALIGN_CENTER or ALIGN_EDGE
 *
 * Example:
 * 		pwmInit(TEMP2, CLK_MCG, 0xFFFF, CMOD0, 0, ALIGN_EDGE);
 */
void pwmInit(uint8_t temp, uint8_t clk, uint16_t max, uint8_t cmod, uint8_t prescaler, uint8_t align){
	switch (temp){
	//Habilita o clock para o temporizador
	case TEMP0:
		SIM->SCGC6 |= (1<<24);
		break;
	case TEMP1:
		SIM->SCGC6 |= (1<<25);
		break;
	case TEMP2:
		SIM->SCGC6 |= (1<<26);
		break;
	default:
		return;
	}

	//Fonte de clock para o temporizador
	switch (clk){
	case CLK_MCG:
		BitSet(SIM->SOPT2, 24);
		BitClr(SIM->SOPT2, 25);
		break;
	case CLK_OSCER:
		BitSet(SIM->SOPT2, 25);
		BitClr(SIM->SOPT2, 24);
		break;
	case CLK_MCGIR:
		SIM->SOPT2 |= (3<<24);
		break;
	default:
		return;
	}
	switch (temp){
	//Frequência do PWM = f_core/(prescaler*MOD) 48Mhz/0xffff = 732 hz
	//MOD = valor máximo da contagem. Valor em que Duty Cicle = 100%
	case TEMP0:
		TPM0->MOD = max;
		break;
	case TEMP1:
		TPM1->MOD = max;
		break;
	case TEMP2:
		TPM2->MOD = max;
		break;
	}

	switch (cmod){
	//Modo de contagem: Interno/Externo
	case CMOD0:
		switch (temp){
		case TEMP0:
			BitSet(TPM0->SC, 3);
			BitClr(TPM0->SC, 4);
			break;
		case TEMP1:
			BitSet(TPM1->SC, 3);
			BitClr(TPM1->SC, 4);
			break;
		case TEMP2:
			BitSet(TPM2->SC, 3);
			BitClr(TPM2->SC, 4);
			break;
		}
		break;

	case CMOD1:
		switch (temp){
		case TEMP0:
			BitSet(TPM0->SC, 4);
			BitClr(TPM0->SC, 3);
			break;
		case TEMP1:
			BitSet(TPM1->SC, 4);
			BitClr(TPM1->SC, 3);
			break;
		case TEMP2:
			BitSet(TPM2->SC, 4);
			BitClr(TPM2->SC, 3);
			break;
		}
		break;
	default:
		return;
	}

	if (prescaler < 8){
	//Prescaler para o timer/counter
		switch (temp){
		case TEMP0:
			TPM0->SC |= prescaler;
			break;
		case TEMP1:
			TPM1->SC |= prescaler;
			break;
		case TEMP2:
			TPM2->SC |= prescaler;
			break;
		}
	}
	else{
		return;
	}

	switch(align){
	//Alinhamento ao centro ou na borda
	case ALIGN_CENTER:
		switch (temp){
		case TEMP0:
			BitSet(TPM0->SC, 5);
			break;
		case TEMP1:
			BitSet(TPM1->SC, 5);
			break;
		case TEMP2:
			BitSet(TPM2->SC, 5);
			break;
		}
		break;
	case ALIGN_EDGE:
		switch (temp){
		case TEMP0:
			BitClr(TPM0->SC, 5);
			break;
		case TEMP1:
			BitClr(TPM1->SC, 5);
			break;
		case TEMP2:
			BitClr(TPM2->SC, 5);
			break;
		}
		break;
	}

}

/* Function: pwmPortInit
 *
 * Configures the pwm in a channel of the timer inicialized
 * by the pwmInit function, enable the clock gate to the port
 * relative to that channel and sets the multiplexer to select
 * the timer to be assinged to the desired pin
 *
 * @param temp is the timer module = TEMP0, TEMP1 or TEMP2
 * @param channel is the timer channel relative to the pin
 * 		TPM0
 * 		Chanel 0: PRTA3,PRTC1,PRTD0,PRTE24
 * 		Chanel 1: PRTA4,PRTC2,PRTD1,PRTE25
 * 		Chanel 2: PRTA5,PRTC3,PRTD2,PRTE29
 * 		Chanel 3: PRTC4,PRTD3,PRTE30
 * 		Chanel 4: PRTC8,PRTD4,PRTE31
 * 		Chanel 5: PRTA0,PRTC9,PRTD5
 *
 * 		TPM1
 * 		Chanel 0: PRTA12,PRTB0,PRTE20
 * 		Chanel 1: PRTA13,PRTB1,PRTE21
 * 		TPM2
 *
 * 		Chanel 0: PRTA1,PRTB2,PRTB18,PRTE22
 * 		Chanel 1: PRTA2,PRTB3,PRTB19,PRTE23
 * @param prt is the port where the pwm will be configured = PRTA, PRTB, PRTC, PRTD or PORTE
 * @param pin is the pin in the port where the pwm is desired
 *
 * Example:
 * 		pwmPortInit(TEMP2, 0, PRTB, 18);
 */
void pwmPortInit(uint8_t temp, uint8_t channel, uint8_t prt, uint8_t pin){

	//Configura o PWM na porta desejada
	switch (temp){
	case TEMP0:
		TPM0->CONTROLS[channel].CnSC |= 0x28;
		break;
	case TEMP1:
		TPM1->CONTROLS[channel].CnSC |= 0x28;
		break;
	case TEMP2:
		TPM2->CONTROLS[channel].CnSC |= 0x28;
		break;
	}

	switch (prt){
	//Seleciona o temporizador no mux de cada pino
	case PRTA:
		SIM->SCGC5 |= (1<<9); //Clock PORTA
		PORTA->PCR[pin] |= (3<<8); //MUX TEMP
		break;

	case PRTB:
		SIM->SCGC5 |= (1<<10);
		PORTB->PCR[pin] |= (3<<8);
		break;

	case PRTC:
		SIM->SCGC5 |= (1<<11);
		if (pin <= 4){
			PORTC->PCR[pin] |= (4<<8);
		}
		else{
			PORTC->PCR[pin] |= (3<<8);
		}
		break;

	case PRTD:
		SIM->SCGC5 |= (1<<12);
		PORTD->PCR[pin] |= (4<<8);
		break;

	case PRTE:
		SIM->SCGC5 |= (1<<13);
		PORTE->PCR[pin] |= (3<<8);
		break;
	}
}


/* Function: pwmDutyCicle
 *
 * Sets the value of the DutyCicle of the signal
 *
 * @param temp is the timer module = TEMP0, TEMP1 or TEMP2
 * @param channel is the timer channel relative to the pin
 * 		TPM0
 * 		Chanel 0: PRTA3,PRTC1,PRTD0,PRTE24
 * 		Chanel 1: PRTA4,PRTC2,PRTD1,PRTE25
 * 		Chanel 2: PRTA5,PRTC3,PRTD2,PRTE29
 * 		Chanel 3: PRTC4,PRTD3,PRTE30
 * 		Chanel 4: PRTC8,PRTD4,PRTE31
 * 		Chanel 5: PRTA0,PRTC9,PRTD5
 *
 * 		TPM1
 * 		Chanel 0: PRTA12,PRTB0,PRTE20
 * 		Chanel 1: PRTA13,PRTB1,PRTE21
 * 		TPM2
 *
 * 		Chanel 0: PRTA1,PRTB2,PRTB18,PRTE22
 * 		Chanel 1: PRTA2,PRTB3,PRTB19,PRTE23
 * @param value is the value corresponding to the dutycicle
 * 		The maximum value (100%) will be the one configured
 * 		in the function pwmInit.
 * 		The minimum value (0%) will be 0.
 *
 * Example:
 * 		pwmDutyCicle(TEMP2, 0, 0x7FF);
 */
void pwmDutyCicle(uint8_t temp, uint8_t channel, uint16_t value){
	switch (temp){
	case TEMP0:
		TPM0->CONTROLS[channel].CnV = value;
		break;
	case TEMP1:
		TPM1->CONTROLS[channel].CnV = value;
		break;
	case TEMP2:
		TPM2->CONTROLS[channel].CnV = value;
		break;
	}
}
