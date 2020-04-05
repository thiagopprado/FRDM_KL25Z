#include "adc.h"

void adcInit(){
	BitSet(SIM->SCGC6, 27); //Habilita o Clock em ADC0
	ADC0->CFG1 = 0b00011100; //Divisor de clock 1/2, Resolucao de 16 bits, Bus Clock
	ADC0->SC1[0] |= 0b11111; // Desabilita o modulo
}

uint16_t adcRead(uint16_t port){
	ADC0->SC1[0] = port; //Inicia conversao
	while(BitTst(ADC0->SC2, 7)); // Coversao em progresso
	while(!BitTst(ADC0->SC1[0], 7)); // Conversao nao esta completa
	return ADC0->R[0];
}
