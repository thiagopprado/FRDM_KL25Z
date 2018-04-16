#include <MKL25Z4.h>

#ifndef DAC_H
#define DAC_H

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & ~(1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

void dacInit();
void dacRead(uint16_t);


#endif
