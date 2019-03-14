//@Autor: Thiago Pereira do Prado

#ifndef SERIALP_H
#define SERIALP_H

#include "fsl_device_registers.h"

#define MAX_NUM 0xFFFF
#define MAX_CASAS 0x20
#define MAX_COEFF 0x0B
#define MAX_BUFF 0xFF
#define ERRO 0xFFFF

// Initial byte: '@'
// Final byte: '$'

typedef struct msg{
	uint8_t data[MAX_BUFF];
	uint8_t position;
} xMessage;


double string_to_float(uint8_t [], uint8_t, uint8_t); // string_to_float(String, posição inicial, posição final)


#endif
