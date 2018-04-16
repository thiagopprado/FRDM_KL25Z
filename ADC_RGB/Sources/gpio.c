#include "gpio.h"

void PORTA_CLK(){
	BitSet(SIM -> SCGC5, 9); //Habilita o clock gate em PORTA.
}
void PORTB_CLK(){
	BitSet(SIM -> SCGC5, 10); //Habilita o clock gate em PORTB.
}
void PORTC_CLK(){
	BitSet(SIM -> SCGC5, 11); //Habilita o clock gate em PORTC.
}
void PORTD_CLK(){
	BitSet(SIM -> SCGC5, 12); //Habilita o clock gate em PORTD.
}
void PORTE_CLK(){
	BitSet(SIM -> SCGC5, 13); //Habilita o clock gate em PORTE.
}

void PORTA_Mode(uint8_t pin, uint8_t mode){
	BitSet(PORTA->PCR[pin], 8); //Configura o pino como GPIO.
	if (mode){ //INPUT
		BitClr(GPIOA->PDDR, pin);
	}
	else{ //OUTPUT
		BitSet(GPIOA->PDDR, pin);
	}
}
void PORTB_Mode(uint8_t pin, uint8_t mode){
	BitSet(PORTB->PCR[pin], 8); //Configura o pino como GPIO.
	if (mode){ //INPUT
		BitClr(GPIOB->PDDR, pin);
	}
	else{ //OUTPUT
		BitSet(GPIOB->PDDR, pin);
	}
}
void PORTC_Mode(uint8_t pin, uint8_t mode){
	BitSet(PORTC->PCR[pin], 8); //Configura o pino como GPIO.
	if (mode){ //INPUT
		BitClr(GPIOC->PDDR, pin);
	}
	else{ //OUTPUT
		BitSet(GPIOC->PDDR, pin);
	}
}
void PORTD_Mode(uint8_t pin, uint8_t mode){
	BitSet(PORTD->PCR[pin], 8); //Configura o pino como GPIO.
	if (mode){ //INPUT
		BitClr(GPIOD->PDDR, pin);
	}
	else{ //OUTPUT
		BitSet(GPIOD->PDDR, pin);
	}
}
void PORTE_Mode(uint8_t pin, uint8_t mode){
	BitSet(PORTE->PCR[pin], 8); //Configura o pino como GPIO.
	if (mode){ //INPUT
		BitClr(GPIOE->PDDR, pin);
	}
	else{ //OUTPUT
		BitSet(GPIOE->PDDR, pin);
	}
}

void PORTA_PULLUP(uint8_t pin){
	BitSet(PORTA->PCR[pin], 1); //Pull Enable
	BitSet(PORTA->PCR[pin], 0); //Pull Up
}
void PORTB_PULLUP(uint8_t pin){
	BitSet(PORTB->PCR[pin], 1); //Pull Enable
	BitSet(PORTB->PCR[pin], 0); //Pull Up
}
void PORTC_PULLUP(uint8_t pin){
	BitSet(PORTC->PCR[pin], 1); //Pull Enable
	BitSet(PORTC->PCR[pin], 0); //Pull Up
}
void PORTD_PULLUP(uint8_t pin){
	BitSet(PORTD->PCR[pin], 1); //Pull Enable
	BitSet(PORTD->PCR[pin], 0); //Pull Up
}
void PORTE_PULLUP(uint8_t pin){
	BitSet(PORTE->PCR[pin], 1); //Pull Enable
	BitSet(PORTE->PCR[pin], 0); //Pull Up
}

void PORTA_Write(uint8_t pin, uint8_t value){
	if(value){ //HIGH
		GPIOA->PSOR = 1<<pin;
		GPIOA->PSOR = 0;
	}
	else{ //LOW
		GPIOA->PCOR = 1<<pin;
		GPIOA->PCOR = 0;
	}
}
void PORTB_Write(uint8_t pin, uint8_t value){
	if(value){ //HIGH
		GPIOB->PSOR = 1<<pin;
		GPIOB->PSOR = 0;
	}
	else{ //LOW
		GPIOB->PCOR = 1<<pin;
		GPIOB->PCOR = 0;
	}
}
void PORTC_Write(uint8_t pin, uint8_t value){
	if(value){ //HIGH
		GPIOC->PSOR = 1<<pin;
		GPIOC->PSOR = 0;
	}
	else{ //LOW
		GPIOC->PCOR = 1<<pin;
		GPIOC->PCOR = 0;
	}
}
void PORTD_Write(uint8_t pin, uint8_t value){
	if(value){ //HIGH
		GPIOD->PSOR = 1<<pin;
		GPIOD->PSOR = 0;
	}
	else{ //LOW
		GPIOD->PCOR = 1<<pin;
		GPIOD->PCOR = 0;
	}
}
void PORTE_Write(uint8_t pin, uint8_t value){
	if(value){ //HIGH
		GPIOE->PSOR = 1<<pin;
		GPIOE->PSOR = 0;
	}
	else{ //LOW
		GPIOE->PCOR = 1<<pin;
		GPIOE->PCOR = 0;
	}
}

uint8_t PORTA_Read(uint8_t pin){
	return (BitTst(GPIOA->PDIR, pin));
}
uint8_t PORTB_Read(uint8_t pin){
	return (BitTst(GPIOB->PDIR, pin));
}
uint8_t PORTC_Read(uint8_t pin){
	return (BitTst(GPIOC->PDIR, pin));
}
uint8_t PORTD_Read(uint8_t pin){
	return (BitTst(GPIOD->PDIR, pin));
}
uint8_t PORTE_Read(uint8_t pin){
	return (BitTst(GPIOE->PDIR, pin));
}