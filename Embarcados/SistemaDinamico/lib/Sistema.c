#include "Sistema.h"

uint16_t ts = 50; //50 ms

#define MAXCOEF 3
int16_t entrada[MAXCOEF], saida[MAXCOEF];
int16_t atual = 0;

#define MAX_X 3
float coefx[MAX_X] = {0,0.0387857,0.0345066};

#define MAX_Y 3
float coefy[MAX_Y] = {1,-1.6314,0.704688};



void initSist(){
	uint8_t i;
	for (i = 0; i < MAXCOEF; i++){
		entrada[i] = 0;
		saida[i] = 0;
	}
	atual = 0;
}

uint16_t equacaoDiff(uint16_t x){
	uint8_t i;
	int16_t anterior;
	uint32_t y = 0;

	entrada[atual] = x;

	for (i = 0; i < MAX_X; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior+= MAXCOEF;
		}
		y+=entrada[anterior]*coefx[i];
	}
	for (i = 1; i < MAX_Y; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior+= MAXCOEF;
		}
		y-=saida[anterior]*coefy[i];
	}
	saida[atual] = y;
	atual ++;
	atual%=MAXCOEF;
	return (int16_t)y;
}

uint16_t getTs(){
	return ts;
}
