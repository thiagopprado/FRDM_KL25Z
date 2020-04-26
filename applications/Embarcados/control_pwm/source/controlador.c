#include "controlador.h"
#include "fsl_device_registers.h"

#define N 19

#define DOUBLE_TO_PF(x) (int32_t)(x*((double)(1<<N)))
#define PF_TO_INT(x) ((int32_t)(x>>N))

#define KD1 (double)0.01 //PID Subida
#define KP1 (double)8.2
#define KI1 (double)1.48

#define KD2 (double)0.02 //PID Descida
#define KP2 (double)7.8
#define KI2 (double)1.3

#define TS 10 //10 ms

int16_t setpoint = 400;
uint8_t sentido = 1;

#define MAXCOEF 3
int16_t entrada[MAXCOEF], saida[MAXCOEF];
int16_t atual = 0;

#define MAX_X 3
int32_t coefx1[MAX_X] = {DOUBLE_TO_PF((KP1 + KI1 * (TS*0.001) + KD1 / (TS*0.001))),
						DOUBLE_TO_PF((-1) * (KP1 + 2 * KD1 / (TS*0.001))),
                        DOUBLE_TO_PF(KD1/(TS*0.001))};

int32_t coefx2[MAX_X] = {DOUBLE_TO_PF((KP2 + KI2 * (TS*0.001) + KD2 / (TS*0.001))),
						DOUBLE_TO_PF((-1) * (KP2 + 2 * KD2 / (TS*0.001))),
                        DOUBLE_TO_PF(KD2/(TS*0.001))};

#define MAX_Y 3
int32_t coefy[MAX_Y] = {DOUBLE_TO_PF(1), DOUBLE_TO_PF(-1), 0};

void initSist(){
    uint8_t i;
    for (i = 0; i < MAXCOEF; i++){
        entrada[i] = 0;
        saida[i] = 0;
    }
    atual = 0;
}

uint16_t getTs(){
    return TS;
}
int16_t equacaoDiff(int16_t x){
    uint8_t i;
    int16_t anterior;
    int64_t y = 0;

    entrada[atual] = setpoint - x; //Realimentação

    for (i = 0; i < MAX_X; i++){
        anterior = atual - i;
        if (anterior < 0){
            anterior+= MAXCOEF;
        }
        if (sentido){
        	y+= ((int64_t)entrada[anterior])*coefx1[i]; //PID Subida, setpoint > atual
        }
        else{
        	y+= ((int64_t)entrada[anterior])*coefx2[i]; //y = int*pf = pf
        }
    }
    for (i = 1; i < MAX_Y; i++){
        anterior = atual - i;
        if (anterior < 0){
            anterior+= MAXCOEF;
        }
        y-=((int64_t)saida[anterior])*coefy[i];
    }
    y = PF_TO_INT(y);

    //saturação
    if (y > 0x7FFF){
    	y = 0x7FFF;
    }
	if (y < -32767){
		y = -32767;
	}

    saida[atual] = y;
    atual ++;
    atual%=MAXCOEF;
    return y;
}

void setSetpoint(uint16_t sp, uint16_t vatual){
	setpoint = sp;
	if (sp > vatual){
		sentido = 1; //Sentido positivo (subida)
	}
	else{
		sentido = 0;
	}
	initSist();
}
