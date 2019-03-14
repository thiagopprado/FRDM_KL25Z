#include "sistemaDinamico.h"
#include "gpio_x.h"

SemaphoreHandle_t mutexEqDiff = NULL;

int32_t setPoint = -1;
uint32_t start = 0;

int32_t atual = 0;

#if PF == 1
coeficientesInt diffInt;
#endif

#if PF == 1
int32_t saida[MAX_COEFF];
#elif PF == 2
float saida[MAX_COEFF];
#elif PF == 3
double saida[MAX_COEFF];
#endif

int32_t entrada[MAX_COEFF];
coeficientes diff;


#if PF == 1
	int64_t temp;
#elif PF == 2
	float temp;
#elif PF == 3
	double temp;
#endif

void initSist(){

	PORTB_Mode(19, OUTPUT);
	PORTB_Write(19, LOW);

	mutexEqDiff = xSemaphoreCreateMutex();
	uint32_t i;
	
#if PF == 1
	diffInt.ultimoIn = 0;
	diffInt.ultimoOut = 0;
	diffInt.amostragem = 500;

#endif
	diff.ultimoIn = 0;
	diff.ultimoOut = 0;
	diff.amostragem = 500;

	for (i = 0; i<MAX_COEFF; i++){
	   	diff.in[i] = 0;
	  	diff.out[i] = 0;
	  	entrada[i] = 0;
		saida[i] = 0;
#if PF == 1
	  	diffInt.in[i] = 0;
	  	diffInt.out[i] = 0;
#endif
	}


	atual = 0;
}

void reset(){
	uint32_t i = 0;

	for (i = 0; i<MAX_COEFF; i++){
	  	entrada[i] = 0;
	  	saida[i] = 0;
	  	temp = 0;
	}

	atual = 0;
}

void setDiff(coeficientes *x){

	if (xSemaphoreTake(mutexEqDiff, portMAX_DELAY)){

		diff.ultimoIn = x->ultimoIn;
		diff.ultimoOut = x->ultimoOut;
		diff.amostragem = x->amostragem;

		uint32_t i;

		//TODO Normalizar

		if(x->out[0] != 0){
			for (i = 0; i<x->ultimoIn; i++){
				diff.in[i] = x->in[i]/x->out[0];
			}
			for (i = x->ultimoIn; i<MAX_COEFF; i++){
				diff.in[i] = 0;
			}

			for (i = 0; i<x->ultimoOut; i++){
				diff.out[i] = x->out[i]/x->out[0];
			}
			for (i = x->ultimoOut; i<MAX_COEFF; i++){
				diff.out[i] = 0;
			}
#if PF == 1
			convertPf();
#endif
			reset();
			xSemaphoreGive(mutexEqDiff);
		}
	}
}

void setPID (double kd, double kp, double ki, uint32_t ta){
	if (xSemaphoreTake(mutexEqDiff, portMAX_DELAY)){
		uint32_t i;
		double ts = (double)ta / 1000; //converte ms em segundos
		diff.in[0] = (kp + ki * ts + kd / ts);
		diff.in[1] = (-1) * (kp + 2 * kd / ts);
		diff.in[2] = kd / ts;
		diff.ultimoIn = 3;

		diff.out[0] = 1;
		diff.out[1] = -1;
		diff.out[2] = 0;
		diff.ultimoOut = 3;

		diff.amostragem = ta*1000; //converte em us

		for (i = diff.ultimoIn; i<MAX_COEFF; i++){
			diff.in[i] = 0;
		}
		for (i = diff.ultimoOut; i<MAX_COEFF; i++){
			diff.out[i] = 0;
		}
#if PF==1
		convertPf();
#endif
		reset();
		setPoint = 1;
		xSemaphoreGive(mutexEqDiff);
	}

}

void setSP(int32_t x){
	setPoint = x;
}


void setStart(uint32_t x){
	if ((x == 1)){
		reset();
	}
	start = x;
	if (start){
		PORTB_Write(19, LOW);
	}
	else{
		PORTB_Write(19, HIGH);
	}

}

uint32_t calculaSist(int32_t sinal){

	int32_t i;


	//Uma entrada (setPoint == -1) ou realimentação negativa (setPoint != -1)
	//TODO criar var pra filtro
	if (setPoint == -1){
		entrada[atual] = sinal;
	}
	else{
		//TODO permitir negativo
		entrada[atual] = (setPoint - sinal); //Entrada tem 12 bits, sem virgula
	}
#if PF==1
	
	//Processamento da equação de diferenças
	int32_t anterior = 0;

	temp = ((int64_t)entrada[atual])*diffInt.in[0];

	for (i = 1; i<diffInt.ultimoIn; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior += MAX_COEFF;
		}
		temp += ((int64_t)entrada[anterior])*diffInt.in[i];
	}

	for (i = 1; i< diff.ultimoOut; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior += MAX_COEFF;
		}
		temp -= ((int64_t)saida[anterior])*diffInt.out[i];
	}

	temp >>=N; //Valor inteiro
	
	//sat tamanho var
	//TODO #define MAXINT32 (1<<32-1)
	if (temp > MAXINT32){
		temp = MAXINT32;
	}
	else if (temp < MININT32){
		temp = MININT32;
	}

	saida[atual] = temp;
	
	//sat saida

	/*if (temp > MAXDAC){ //Maior valor do DAC (12 bits)
		temp = MAXDAC;
	}
	else if (temp < MINDAC){
		temp = MINDAC;
	}*/
	//TODO valor anterior
	atual ++;
	atual %= MAX_COEFF;
	return temp;
#else
	//Processamento da equação de diferenças

	int32_t anterior = 0;


	temp = (diff.in[0]*entrada[atual]);

	for (i = 1; i<diff.ultimoIn; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior += MAX_COEFF;
		}
		temp += (diff.in[i]*entrada[anterior]);
	}

	for (i = 1; i< diff.ultimoOut; i++){
		anterior = atual - i;
		if (anterior < 0){
			anterior += MAX_COEFF;
		}
		temp -= (saida[anterior]*diff.out[i]);
	}
	saida[atual] = temp;
	
	//sat saida
	/*if (temp > MAXDAC){
		temp = MAXDAC;
	}
	else if (temp < MINDAC){
		temp = MINDAC;
	}*/
	
	atual ++;
	atual %= MAX_COEFF;
	return (int32_t)temp;
#endif
}

uint32_t getTime(){
#if PF==1
	return diffInt.amostragem;
#else
	return diff.amostragem;
#endif
}
#if PF == 1
void convertPf(){
	uint32_t i;
	diffInt.amostragem = diff.amostragem;
	diffInt.ultimoIn = diff.ultimoOut;
	diffInt.ultimoOut = diff.ultimoOut;

	for (i = 0; i<diff.ultimoIn; i++){
		diffInt.in[i] = pf(diff.in[i]);
	}
	for (i = 0; i<diff.ultimoOut; i++){
		diffInt.out[i] = pf(diff.out[i]);
	}
}
#endif
