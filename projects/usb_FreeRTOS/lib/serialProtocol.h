//@Autor: Thiago Pereira do Prado

#ifndef SERIALP_H
#define SERIALP_H

#include "fsl_device_registers.h"

#define MAX_NUM 0xFFFF
#define MAX_CASAS 0x20
#define MAX_COEFF 0x0A
#define MAX_BUFF 0xFF

#define DIFF 2
#define PID 3
#define PRINTDIFF 4

// Initial byte: '@'
// Final byte: '$'

//#define uint8_t char
//#define uint32_t int
//#define int64_t long int

typedef struct coef{
    float in[MAX_COEFF], out[MAX_COEFF];
    uint8_t ultimoIn, ultimoOut;
    uint8_t updating;
    uint8_t amostragem;
    uint8_t init_coef;
} coeficientes;

typedef struct msg{
	uint8_t data[MAX_BUFF];
	uint8_t position;
} xMessage;

void updateDiff(coeficientes*);

float string_to_float(uint8_t [], uint8_t, uint8_t);

uint8_t float_to_string(uint8_t [], float); //Retorna o tamanho da string

void coefInit(coeficientes*);

#endif
