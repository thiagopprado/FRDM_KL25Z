#include <MKL25Z4.h>

#ifndef ADC_H
#define ADC_H

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & ~(1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

#define PT_E20 0
#define PT_E22 3
#define PT_E21 4
#define PT_D1 5
#define PT_D5 6
#define PT_D6 7
#define PT_B0 8
#define PT_B1 9
#define PT_C2 11
#define PT_B2 12
#define PT_B3 13
#define PT_C0 14
#define PT_C1 15

void adcInit();
uint16_t acdRead(uint16_t port);


#endif
