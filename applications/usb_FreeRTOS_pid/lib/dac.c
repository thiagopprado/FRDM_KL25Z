#include "dac.h"

void dacInit(){
	BitSet(SIM->SCGC6, 31); //Habilita o Clock em DAC0
	DAC0->SR = 0; //Limpa o registrador
	DAC0->C0 = 0x80; //Habilita o conversor DA
}

void dacWrite(int32_t value){
	if (value < 0){
		DAC0->DAT->DATL = 0x00;
		DAC0->DAT->DATH = 0x00;
	}
	else if(value < 4096){
		DAC0->DAT->DATL = (uint8_t)(value & 0x00FF); //8 bits menos significativos
		DAC0->DAT->DATH = (uint8_t)((value >> 8) & 0x000F); //8 bits mais significativos
	}
	else{
		DAC0->DAT->DATL = 0xFF;
		DAC0->DAT->DATH = 0xF;
	}
}
