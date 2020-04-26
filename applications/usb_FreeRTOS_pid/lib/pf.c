#include "pf.h"

int32_t soma (int32_t a, int32_t b){
    int64_t temp;
    temp = (int64_t)a + (int64_t)b;

    //Saturação
    if(temp > int32_MAX){
        temp = int32_MAX;
    }
    if(temp < int32_MIN){
        temp = int32_MIN;
    }

    return (int32_t) temp;
}
int32_t sub (int32_t a, int32_t b){
    return a - b;
}

int32_t mult (int32_t a, int32_t b){
    int64_t temp;

    temp = (int64_t)a * (int64_t)b;
    //temp += K; //Arredondamento
    temp = temp >> N; //Correção

    //Saturação
    if(temp > int32_MAX){
        temp = int32_MAX;
    }
    if(temp < int32_MIN){
        temp = int32_MIN;
    }

    return (int32_t)temp;
}

int32_t divisao(int32_t a, int32_t b){
    int64_t temp;

    temp = (int64_t)a<<N;
    temp += (b>>1);  // soma b/2 para arredondar o resultado

    return (int32_t)(temp/(int64_t)b);
}
