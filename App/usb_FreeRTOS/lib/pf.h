#ifndef pf_H
#define pf_H

#include "fsl_device_registers.h"

#define int32_MAX 2147483647
#define int32_MIN -2147483647

#define IN 12
#define N ((32-IN)-1)
#define K (1<<(N-1))

#define pf_to_float(x) ((double)x/(double)(1<<N))
#define pf(x) (int32_t)(x*(double)(1<<N))

//#define sub(a,b) (a-b)


//#define soma(a,b) (a+b)


//#define mul(a,b) ((((int64_t)a * b) > MAX) ? MAX : (int64_t)a*b)



int32_t soma (int32_t a, int32_t b);

int32_t sub (int32_t a, int32_t b);

int32_t mult (int32_t a, int32_t b);

int32_t divisao(int32_t a, int32_t b);

#endif
