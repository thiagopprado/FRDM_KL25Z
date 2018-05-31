/*
e * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "gpio.h"

static uint8_t valor = 0;

void delay (){
	float b;
	for (b = 0; b<100; b++);
}
void kpDebounce(){
	static unsigned char anterior = 0;
	static unsigned char atual = 0;
	static unsigned char tempo = 12;
	if(!PORTB_Read(8)){
		BitSet(atual, 0);
	}
	else{
		BitClr(atual, 0);
	}
	if(!PORTB_Read(9)){
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
uint8_t kpRead(){
	return valor;
}

int main(void)
{
	PORTB_CLK(); //Clk PORTB

	PORTB_Mode(8, OUTPUT); //Output - LED
	PORTB_Mode(9, INPUT); //Input - Botao ++
	PORTB_Mode(10, INPUT); //Input - Botao --

	PORTB_PULLUP(8);
	PORTB_PULLUP(9);

	uint32_t target = 0;
	uint32_t cont = 0;
	uint8_t anterior = 0;
	uint8_t novo = 0;

    for (;;) {
    	kpDebounce();
    	novo = kpRead();
    	if ((novo != anterior)&&(novo == 0)){
    		if (BitTst(anterior, 1)){
    			if (target < 100)
    				target = 100;

    			target-=50;
    		}
    		if (BitTst(anterior, 0)){
    			target+=50;
    		}
    	}
    	if (cont < target){
    		PORTB_Write(10, HIGH);
    	}
    	else{
    		if (cont < target*2){
    			PORTB_Write(10, LOW);
    		}
    		else{
    			cont = 0;
    			PORTB_Write(10, HIGH);
    		}
    	}
    	anterior = novo;
    	cont ++;
     	delay();

    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
