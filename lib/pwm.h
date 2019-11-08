//@Autor: Thiago Pereira do Prado

#ifndef PWM_H
#define PWM_H

#include <MKL25Z4.h>
#include "fsl_device_registers.h"

#define BitSet(arg, bit) (arg |= (1<<bit))
#define BitClr(arg, bit) (arg &= ~(1<<bit))
#define BitTst(arg, bit) (arg & (1<<bit))
#define BitFlp(arg, bit) (arg ^= (1<<bit))

#define TEMP0 0
#define TEMP1 1
#define TEMP2 2

#define CLK_MCG 0
#define CLK_OSCER 1
#define CLK_MCGIR 2

#define CMOD0 0
#define CMOD1 1

#define ALIGN_CENTER 0
#define ALIGN_EDGE 1

#define PRTA 0
#define PRTB 1
#define PRTC 2
#define PRTD 3
#define PRTE 4

void pwmInit(uint8_t temp, uint8_t clk, uint16_t max, uint8_t cmod, uint8_t prescaler, uint8_t align);
void pwmPortInit(uint8_t temp, uint8_t channel, uint8_t prt, uint8_t pin);
void pwmDutyCicle(uint8_t temp, uint8_t channel, uint16_t value);

#endif
