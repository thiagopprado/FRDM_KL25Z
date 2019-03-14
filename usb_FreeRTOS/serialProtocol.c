#include "serialProtocol.h"

double string_to_float (uint8_t vetor[], uint8_t inicio, uint8_t fim){

	uint8_t i, ponto = 0, flag_ponto = 0, elevado = 0;
	double valor_temp = 0, flag_menos = 1;

	for (i = inicio; i< fim; i++){
		if (vetor[i] == 'e'){
			i++;
			break;
		}
		if ((vetor[i] >= '0') && (vetor[i] <= '9')){
			valor_temp = (valor_temp*10) + (vetor[i] - '0'); //Armazena o valor sem virgulas
		}
		else{   //Verifica possiveis erros como a ocorrencia de 2 pontos ou caracter invalido
			if (flag_ponto){
				return ERRO; //2 pontos
			}
			else{
                if((i == inicio) && (vetor[i] == '-')){
                    flag_menos = -1;
                }
                else{
                    if (vetor[i] != '.') //Caracter invalido
                        return ERRO;
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
	for (;i<fim; i++){
		if((vetor[i] >= '0') && (vetor[i] <= '9')){
			elevado*=10;
			elevado += vetor[i]-'0';
		}
		else{
			return ERRO;
		}
	}
	for (i = 0; i < elevado; i++){
		valor_temp *= 10;
	}
	for (i = 0; i < ponto; i++){
		valor_temp /= 10;
	}

	return flag_menos*valor_temp;
}

