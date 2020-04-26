#ifndef SISTEMA_H
#define SISTEMA_H

#include "fsl_device_registers.h"

void initSist();
uint16_t getTs();
uint16_t equacaoDiff(uint16_t);

#endif
