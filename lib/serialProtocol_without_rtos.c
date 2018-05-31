#include "serialProtocol.h"
//#include "gpio_x.h"
#include <stdio.h>
//Coeficientes recebidos

static float entrada[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t lastIn = 0;
static float saida[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t lastOut = 0;
static uint8_t tempo = 0;

static float pid[3] = {0, 0, 0};

//Protocolo Serial
uint8_t init = 0;
uint8_t position = 0;
uint8_t data[MAX_BUFF];

uint8_t process (uint8_t dados){
	if (dados == '@'){
		position = 0;
		init = 1;
		return 0;
	}
	if (dados == '$'){

		//position = 0;

		if (init){
			init = 0;
			return 1; //Mensagem pronta para ser interpretada
		}
		init = 0;
		return 0;
	}
	if (init){
		data[position] = dados;
		position++;

		if (position > MAX_BUFF){
			//Wrong message
			position = 0;
			init = 0;
		}

	}
	return 0;
}

uint8_t interpret (){
	if ((data[0] == 'e') && (data[1] == ',')){ //Byte de entrada
			int atual = 0, inicio = 2, i, flag_s = 0;

			for (i = 2; i < position; i++){ //Procura a virgula
				if (data[i] == 's'){ //Byte de saída
					if (flag_s) //s duas vezes
						return 0;
					if (data[i+1] == ','){
						atual = 0;
						flag_s = 1;
						inicio = i+2;
						i++;
						continue;
					}
					return 0; //Erro (faltou a virgula)
				}
				if(!flag_s){ //Coeficientes de entrada
					if (data[i] == ','){
						entrada[atual] = string_to_float(data, inicio, i);
						if (entrada[atual] == -1)
							return 0;
						atual++;
						inicio = i + 1;
						lastIn = atual;
					}
				}
				else{ //Coeficientes de saída
					if (data[i] == ','){
                        saida[atual] = string_to_float(data, inicio, i);
						if (saida[atual] == -1)
							return 0;
						atual++;
						inicio = i + 1;
						lastOut = atual;
						if (data[i+1] == 't'){ //Tempo de amostragem
                            if (data[i+2] == ','){
                                tempo = string_to_float(data, i+3, position-1);
                                if (tempo > 0){
                                    return DIFF;
                                }
                                return 0;
                            }
                            else{
                                return 0;
                            }
                        }
					}
				}
			}
			return 0;
		}

		if ((data[0] == 'p') && (data[1] == 'i')&&(data[2] == 'd') && (data[3] == ',')){

		}

		uint8_t txt [] = "print";
		int i;
		for (i = 0; i<5; i++){
			if (data[i] != txt[i]){
				break;
			}
		}
		if (i == 5){
			return PRINTDIFF;
		}

		return 0;
	}

float string_to_float (uint8_t vetor[], uint8_t inicio, uint8_t fim){

	uint8_t i, ponto = 0, flag_ponto = 0;
	float valor_temp = 0, flag_menos = 1;

	for (i = inicio; i< fim; i++){
		if ((vetor[i] >= '0') && (vetor[i] <= '9')){
			valor_temp = (valor_temp*10) + vetor[i] - '0'; //Armazena o valor sem virgulas
		}
		else{   //Verifica possiveis erros como a ocorrencia de 2 pontos ou caracter invalido
			if (flag_ponto){
				return -1; //2 pontos
			}
			else{
                if((i == inicio) && (vetor[i] == '-')){
                    flag_menos = -1;
                }
                else{
                    if (vetor[i] != '.') //Caracter invalido
                        return -1;
                }
			}
		}
		if(flag_ponto){
			ponto ++;
		}
		if (vetor[i] == '.'){
			flag_ponto = 1;
		}
	}
	for (i = 0; i < ponto; i++){
		valor_temp /= 10;
	}

	return flag_menos*valor_temp;
}

uint32_t elevado(uint32_t x, uint8_t y){
    uint32_t valor = 1, i;
    for (i = 0; i<y; i++){
        valor*=x;
    }
    return valor;
}

uint8_t float_to_string(uint8_t string[], float numero){
    uint8_t i = 0, j, flag_menos = 0;
    int64_t numeroInt = numero *10000;

    if (numero < 0){
        flag_menos = 1;
        numeroInt*=(-1);
    }
    if(numero < MAX_NUM){
        for (i = 0; i<MAX_CASAS; i++){
            if (numeroInt < elevado(10, i))
                break;
        }
        if (i == MAX_CASAS){
            return 0;
        }
        if(flag_menos){
            string[0] = '-';
        }
        for(j=0+flag_menos; j<(i-4+flag_menos); j++){
            string[j] = (numeroInt/elevado(10, i-1-j+flag_menos))%10 + '0';
        }
        if ((j==0)||((flag_menos==1) && (j == 1))){
        	string[j] = '0';
        	j++;
        }
        string[j] = '.';
        string[j+1] = (numeroInt/1000)%10 + '0';
        string[j+2] = (numeroInt/100)%10 + '0';
        string[j+3] = (numeroInt/10)%10 + '0';
        string[j+4] = numeroInt%10 + '0';
        string[j+5] = '\0';

    }
    //printf ("\nNumero1: %d\nNumero2: %d\n", j+5, i+1+flag_menos);
    return j+5; //Compensa o decremento e o ponto
}

void updateDiff(coeficientes *x){
    int i;
    x->updating = 1;

    x->init_coef = 1; // Sinaliza que ja foi realizado ao menos o primeiro update
    x->amostragem = tempo;
    for (i = 0; i<lastIn; i++){
        x->in[i] = entrada[i];
    }
    x->ultimoIn = lastIn;
    for (i = 0; i<lastOut; i++){
        x->out[i] = saida[i];
    }
    x->ultimoOut = lastOut;

    x->updating = 0;
}

void coefInit(coeficientes* atual){
	atual->ultimoIn = 0;
	atual->ultimoOut = 0;
	atual->updating = 0;
	atual->amostragem = 0;
	atual->init_coef = 0;

	uint8_t i;
	for (i = 0; i<10; i++){
	   	atual->in[i] = 0;
	   	atual->out[i] = 0;
	}
}
