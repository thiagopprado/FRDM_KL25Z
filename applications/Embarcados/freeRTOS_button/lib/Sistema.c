#include "Sistema.h"

#define N 19
#define BASE (1<<N)

uint16_t ts = 50; //50 ms

#define MAXCOEF 3
int16_t entrada[MAXCOEF], saida[MAXCOEF];
int16_t atual = 0;

#define MAX_X 3
int32_t coefx[MAX_X] = {0*BASE,0.0387857*BASE,0.0345066*BASE};

#define MAX_Y 3
int32_t coefy[MAX_Y] = {1*BASE,-1.6314*BASE,0.704688*BASE};


/*#define MAX_X 5
int32_t coefx[MAX_X] = {1, 1, 1, 1, 1};

#define MAX_Y 5
int32_t coefy[MAX_Y] = {1, 1, 1, 1, 1};
*/

void initSist(){
    uint8_t i;
    for (i = 0; i < MAXCOEF; i++){
        entrada[i] = 0;
        saida[i] = 0;
    }
    atual = 0;
}

uint16_t getTs(){
    return ts;
}
uint16_t equacaoDiff(uint16_t x){
    uint8_t i;
    int16_t anterior;
    int64_t y = 0; //64 bits para evitar overflow na soma de 32 + 32 bits

    entrada[atual] = x; //Entrada = uint 12 bits

    for (i = 0; i < MAX_X; i++){
        anterior = atual - i;
        if (anterior < 0){
            anterior+= MAXCOEF;
        }
        y += entrada[anterior]*coefx[i]; //y = inteiro*ponto fixo = ponto fixo
    }
    for (i = 1; i < MAX_Y; i++){
        anterior = atual - i;
        if (anterior < 0){
            anterior+= MAXCOEF;
        }
        y -= saida[anterior]*coefy[i]; // inteiro*ponto fixo
    }
    y >>= 19; //Y em ponto fixo é convertido para inteiro
    saida[atual] = y;
    atual ++;
    atual%=MAXCOEF;
    return (int16_t)y;
}
