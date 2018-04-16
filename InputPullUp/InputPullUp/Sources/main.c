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

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & ((int)1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

static unsigned char valor = 0;

void delay (){
	float b;
	for (b = 0; b<10; b++);
}
void kpDebounce(){
	static unsigned char anterior = 0;
	static unsigned char atual = 0;
	static unsigned char tempo = 12;
	if(!BitTst(GPIOB->PDIR, 8)){
		BitSet(atual, 0);
	}
	else{
		BitClr(atual, 0);
	}
	if(!BitTst(GPIOB->PDIR, 9)){
		BitSet(atual, 1);
	}
	else{
		BitClr(atual, 1);
	}
	if (atual == anterior){
		tempo --;
	}
	else{
		anterior = atual;
		tempo = 12;
	}
	if (tempo == 0){
		valor = atual;
	}
}
unsigned char kpRead(){
	return valor;
}

int main(void)
{
	BitSet(SIM -> SCGC5, 10); //Clk PORTB
	PORTB->PCR[8] |= 0x100; //GPIO
	PORTB->PCR[9] |= 0x100;
	PORTB->PCR[10] |= 0x100;

	BitSet(PORTB -> PCR[8], 1); //Pull Enable
	BitSet(PORTB -> PCR[9], 1);
	BitSet(PORTB -> PCR[8], 0); //Pull Up
	BitSet(PORTB -> PCR[9], 0);

	BitSet(GPIOB->PDDR, 10); //Output - LED
	BitClr(GPIOB->PDDR, 9); //Input - Botao ++ com PullUp
	BitClr(GPIOB->PDDR, 8); //Input - Botao --

	unsigned long int target = 0;
	unsigned long int cont = 0;
	unsigned char anterior = 0;
	unsigned char novo = 0;

    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
    	kpDebounce();
    	novo = kpRead();
    	if ((novo != anterior)&&(novo == 0)){
    		if (BitTst(anterior, 1)){
    			if (target < 1000)
    				target = 1000;

    			target-=500;
    		}
    		if (BitTst(anterior, 0)){
    			target+=500;
    		}
    	}
    	if (cont < target){
    		GPIOB->PSOR = (1<<10);
    		GPIOB->PSOR = 0;
    	}
    	else{
    		if (cont < target*2){
    			GPIOB->PCOR = (1<<10);
    			GPIOB->PCOR = 0;
    		}
    		else{
    			cont = 0;
    			GPIOB->PSOR = (1<<10);
    			GPIOB->PSOR = 0;
    		}
    	}
    	anterior = novo;
    	cont ++;
     	delay();





    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
