/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
//#include "MKL25Z4.h"

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg &= (1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))


void delay (){
	float a, b;
	for (a = 0; a<10; a++){
		for (b = 0; b<7000; b++);
	}
}

int main(void){
	//Versão sem BitSet/Clr

	/*
	SIM -> SCGC5 |= (1<<10); //Habilita o clock em PORTB. Pag. 206
	SIM -> SCGC5 |= (1<<12); //clk PORTD

				//  (1<<9) PORTA
				// (1<<10) PORTB
				// (1<<11) PORTC
				// (1<<12) PORTD
				// (1<<13) PORTE

	PORTB -> PCR[18] |= 0x100; //Configura o Pino como GPIO. Pag. 184
	PORTB -> PCR[19] |= 0x100;
	PORTD -> PCR[1] |= 0x100;

	GPIOB -> PDDR |= (1<<18); //0 = Input; 1 = Output. Pag. 778
	GPIOB -> PDDR |= (1<<19);
	GPIOD -> PDDR |= (1<<1);

	GPIOB -> PDOR |= (1<<18); //Leva para nivel 1 (desliga o led)
	GPIOB -> PDOR |= (1<<19);
	GPIOD -> PDOR |= (1<<1);

	//PDDR 0 - in; 1 - out
	//PDOR Seta nivel 0 ou 1
	//PDIR Input Register

	//PCOR Leva o pino para nivel logico 0
	//PSOR Seta o pino de PDOR para nivel 1
	//PTOR inverte

    for (;;) { //ever

    	//Vermelho
    	GPIOB -> PDOR &= ~(1<<18); //Nivel 0
    	delay();
    	GPIOB -> PDOR |= (1<<18); //Nivel 1
    	delay();

    	//Verde
    	GPIOB -> PDOR &= ~(1<<19); //Nivel 0
    	delay();
    	GPIOB -> PDOR |= (1<<19); //Nivel 1
    	delay();

    	//Azul
    	GPIOD -> PDOR &= ~(1<<1); //Nivel 0
    	delay();

    	GPIOD -> PDOR |= (1<<1); //Nivel 1
    	delay();
    }
	*/

	//Versão com BitSet/Clr

	BitSet(SIM -> SCGC5, 10); //Habilita o clock em PORTB. Pag. 206
	BitSet(SIM -> SCGC5, 12); //clk PORTD

				//  (9) PORTA
				// (10) PORTB
				// (11) PORTC
				// (12) PORTD
				// (13) PORTE

	BitSet(PORTB -> PCR[18], 8); //Configura o Pino como GPIO. Pag. 184
	BitSet(PORTB -> PCR[19], 8);
	BitSet(PORTD -> PCR[1], 8);

	BitSet(GPIOB -> PDDR, 18); //0 = Input; 1 = Output. Pag. 778
	BitSet(GPIOB -> PDDR, 19);
	BitSet(GPIOD -> PDDR, 1);

	BitSet(GPIOB -> PDOR, 18); //Leva para nivel 1 (RGB Ativo por zero)
	BitSet(GPIOB -> PDOR, 19);
	BitSet(GPIOD -> PDOR, 1);

	//PDDR 0 - in; 1 - out
	//PDOR Seta nivel 0 ou 1
	//PDIR Input Register

	//PCOR Leva o pino para nivel logico 0
	//PSOR Seta o pino de PDOR para nivel 1
	//PTOR inverte

	for (;;) { //ever
	/*
	   	//Sequencial

	   	//Vermelho
	   	BitClr(GPIOB -> PDOR, 18); //Nivel 0
	   	delay();
	   	BitSet(GPIOB -> PDOR, 18); //Nivel 1
	   	delay();

	   	//Verde
	   	BitClr(GPIOB -> PDOR, 19); //Nivel 0
	   	delay();
	   	BitSet(GPIOB -> PDOR, 19); //Nivel 1
	   	delay();

	   	//Azul
	   	BitClr(GPIOD -> PDOR, 1); //Nivel 0
	   	delay();
	   	BitSet(GPIOD -> PDOR, 1); //Nivel 1
	    delay();
	*/
		//random
		if(rand()%2){
			BitClr(GPIOB -> PDOR, 18);
		}

		if(rand()%2){
			BitClr(GPIOB -> PDOR, 19);
		}

		if(rand()%2){
			BitClr(GPIOD -> PDOR, 1);
		}
		delay();

		BitSet(GPIOD -> PDOR, 1);
		BitSet(GPIOB -> PDOR, 18);
		BitSet(GPIOB -> PDOR, 19);

		delay();
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
