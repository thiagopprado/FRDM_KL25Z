#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "fsl_device_registers.h"

void initSist();

uint16_t getTs();
int16_t equacaoDiff(int16_t x);

void setSetpoint(uint16_t sp, uint16_t vatual);

#endif /* CONTROLADOR_H_ */
