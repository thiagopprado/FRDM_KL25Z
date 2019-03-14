//Autor: Thiago Pereira do Prado

#ifndef GPIOX_H
#define GPIOX_H

//#include <MKL25Z4.h>
#include "fsl_device_registers.h"

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & (1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

#define OUTPUT 0
#define INPUT 1

#define LOW 0
#define HIGH 1

void PORTA_CLK(); //Habilita o clock da PORTA
void PORTB_CLK(); //Habilita o clock da PORTB
void PORTC_CLK(); //Habilita o clock da PORTC
void PORTD_CLK(); //Habilita o clock da PORTD
void PORTE_CLK(); //Habilita o clock da PORTE

void PORTA_Mode(uint8_t pin, uint8_t mode); //Configura um pino da PORTA como INPUT ou OUTPUT
void PORTB_Mode(uint8_t pin, uint8_t mode); //Configura um pino da PORTB como INPUT ou OUTPUT
void PORTC_Mode(uint8_t pin, uint8_t mode); //Configura um pino da PORTC como INPUT ou OUTPUT
void PORTD_Mode(uint8_t pin, uint8_t mode); //Configura um pino da PORTD como INPUT ou OUTPUT
void PORTE_Mode(uint8_t pin, uint8_t mode); //Configura um pino da PORTE como INPUT ou OUTPUT

void PORTA_PULLUP(uint8_t pin); //Habilita PULLUP no pino da PORTA se configurado como INPUT
void PORTB_PULLUP(uint8_t pin); //Habilita PULLUP no pino da PORTB se configurado como INPUT
void PORTC_PULLUP(uint8_t pin); //Habilita PULLUP no pino da PORTC se configurado como INPUT
void PORTD_PULLUP(uint8_t pin); //Habilita PULLUP no pino da PORTD se configurado como INPUT
void PORTE_PULLUP(uint8_t pin); //Habilita PULLUP no pino da PORTE se configurado como INPUT

void PORTA_Write(uint8_t pin, uint8_t value); //Coloca o nível lógico de um pino da PORTA em LOW ou HIGH
void PORTB_Write(uint8_t pin, uint8_t value); //Coloca o nível lógico de um pino da PORTB em LOW ou HIGH
void PORTC_Write(uint8_t pin, uint8_t value); //Coloca o nível lógico de um pino da PORTC em LOW ou HIGH
void PORTD_Write(uint8_t pin, uint8_t value); //Coloca o nível lógico de um pino da PORTD em LOW ou HIGH
void PORTE_Write(uint8_t pin, uint8_t value); //Coloca o nível lógico de um pino da PORTE em LOW ou HIGH

uint8_t PORTA_Read(uint8_t pin); //Retorna o nível lógico de um pino da PORTA
uint8_t PORTB_Read(uint8_t pin); //Retorna o nível lógico de um pino da PORTB
uint8_t PORTC_Read(uint8_t pin); //Retorna o nível lógico de um pino da PORTC
uint8_t PORTD_Read(uint8_t pin); //Retorna o nível lógico de um pino da PORTD
uint8_t PORTE_Read(uint8_t pin); //Retorna o nível lógico de um pino da PORTE


#endif
