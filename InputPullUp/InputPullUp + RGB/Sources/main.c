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
#define BitTst(arg, bit) (arg & ((int)1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))


void delay (){
	float a, b;
	for (a = 0; a<10; a++){
		for (b = 0; b<7000; b++);
	}
}

int main(void){

	BitSet(SIM -> SCGC5, 10); //Clk PORTB
	BitSet(SIM -> SCGC5, 12); //Clk PORTD

	BitSet(PORTB -> PCR[18], 8); //GPIO
	BitSet(PORTB -> PCR[19], 8);
	BitSet(PORTD -> PCR[1], 8);

	BitSet(PORTB -> PCR[8], 8); //GPIO
	BitSet(PORTB -> PCR[9], 8);
	BitSet(PORTB -> PCR[10], 8);

	BitSet(PORTB -> PCR[8], 1); //Pull Enable
	BitSet(PORTB -> PCR[9], 1);
	BitSet(PORTB -> PCR[10], 1);

	BitSet(PORTB -> PCR[8], 0); //Pull Up
	BitSet(PORTB -> PCR[9], 0);
	BitSet(PORTB -> PCR[10], 0);

	BitClr(GPIOB -> PDDR, 8); //Input
	BitClr(GPIOB -> PDDR, 9);
	BitClr(GPIOB -> PDDR, 10);

	BitSet(GPIOB -> PDDR, 18); //Output
	BitSet(GPIOB -> PDDR, 19);
	BitSet(GPIOD -> PDDR, 1);


	GPIOB->PSOR = (1<<18)|(1<<19); //Leva para nivel 1 (RGB Ativo por zero)
	GPIOB->PSOR = 0;
	GPIOD->PSOR = (1<<1);
	GPIOD->PSOR = 0;

	for (;;) { //ever

	   	//Sequencial

	   	//Vermelho
		if (BitTst(GPIOB->PDIR, 8)){
			GPIOB->PSOR = (1<<18); //Nivel 1
			GPIOB->PSOR = 0;
		}
		else{

	   		GPIOB->PCOR = (1<<18); //Nivel 0
	   		GPIOB->PCOR = 0;
		}

	   	//Verde
		if (BitTst(GPIOB->PDIR, 9)){
			GPIOB->PSOR = (1<<19); //Nivel 1
			GPIOB->PSOR = 0;
		}
		else{
			GPIOB->PCOR = (1<<19); //Nivel 0
			GPIOB->PCOR = 0;
		}

	   	//Azul
	    if (BitTst(GPIOB->PDIR, 10)){
	    	GPIOD->PSOR = (1<<1); //Nivel 1
	    	GPIOD->PSOR = 0;
	    }
	    else{
	    	GPIOD->PCOR = (1<<1); //Nivel 0
	    	GPIOD->PCOR = 0;
	    }


    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

