#ifndef BUTTN_H
#define BUTTN_H

#include "fsl_device_registers.h"

void bInit(); //Inicializa a porta digital e liga PullUP

void bDebounce(); //Rotina de debounce que analisa a estabilidade da porta

uint8_t bRead(); //Retorna o valor lido

#endif
