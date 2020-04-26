//@Autor: Thiago Pereira do Prado

#ifndef DAC_H
#define DAC_H

//#include <MKL25Z4.h>
#include "fsl_device_registers.h"

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & (1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

void dacInit();
void dacWrite(int32_t);
//DAC0 = PTE30

#endif
