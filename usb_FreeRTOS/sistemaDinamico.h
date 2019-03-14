#ifndef SISDIN_H
#define SISDIN_H

#include "FreeRTOS.h"
#include "semphr.h"
#include "serialProtocol.h"
#include "fsl_device_registers.h"
#include "pf.h"

#define PF 1 	/* 1 Ponto Fixo
				   2 float
				   3 double
 	 	 	 	*/

#define MAXINT32 0x7fffffff
#define MININT32 -0x7fffffff
#define MAXDAC 0x0FFF
#define MINDAC 0

typedef struct coef{
#if PF == 2
	float in[MAX_COEFF], out[MAX_COEFF];
#else
    double in[MAX_COEFF], out[MAX_COEFF];

#endif
    uint32_t ultimoIn, ultimoOut;
    uint32_t amostragem;
} coeficientes;

typedef struct coefInt{
    int32_t in[MAX_COEFF], out[MAX_COEFF];
    uint32_t ultimoIn, ultimoOut;
    uint32_t amostragem;
} coeficientesInt;

void initSist();

void setDiff(coeficientes*);

void setPID(double, double, double, uint32_t);

void setSP(int32_t);

void setStart(uint32_t);

uint32_t calculaSist(int32_t);

uint32_t getTime();

#if PF == 1
void convertPf();
#endif

#endif
