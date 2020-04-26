#define DS 8
#define EN 10
#define CLK 11

#define DIR 12
#define ESQ 13

static int valor = 0x0000;
static unsigned char tempo;
void setup(){
	serialInit();
	kpInit();
	Serial.begin(9600);
}

void loop(){
  kpDebounce();
  static int a;
  a = kpRead();
  if (a){
    Serial.print("Teclas pressionadas: ");
	  for (int i = 0; i< 10; i++){
        if (a & 1<<i){ // Analiza cada bit da variável que representa o estado dos botões
	      Serial.print(i);
          Serial.print(" ");
        }
      
  	}
    Serial.print("\n");
  }
}

void kpInit(){
	pinMode(DIR, INPUT); // Configura as portas como entrada
	pinMode(ESQ, INPUT);
}
int kpRead(){
	return valor; // Retorna o valor atualizado na função kpDebounce()
}
void kpDebounce(){
	static int novo = 0x0000; // As duas variáveis static não são descartadas quando o código sai da função
	static int antigo = 0x0000; // As duas declarações só são executadas na primeira chamada da função
	for (unsigned char i = 0; i<5; i++){
		serialWrite(1<<(i+1)); // Liga as portas Q1 até Q5, uma por vez
		if (digitalRead(DIR)){ // Verifica se o botao referente à porta ligada na linha anterior foi apertado
			novo |= (int)1<<i; // Coloca o bit em 1 se o botao é pressionado
		}
      	else{
          novo &= ~(1<<i); // Coloca o bit em 0 se o botao não é pressionado
        }
		if (digitalRead(ESQ)){
			novo |= (int)1<<(i+5);
		}
      	else{
          novo &= ~(1<<(i+5));
      	}
	}
	if (novo == antigo){ //Se os botoes estabilizaram
		tempo--;
	}
	else{ //Ruído
		antigo = novo;
		tempo = 12;
	}
	if (!tempo){ // Entrada estabilizada durante 12 chamadas da função debounce
		valor = novo; // Atualiza o valor retornado por kpRead, em que cada bit representa um botao ligado ou desligado
	}
}
void serialInit(){
  pinMode(DS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(CLK, OUTPUT);
  
  digitalWrite(DS, LOW);
  digitalWrite(EN, LOW);
  digitalWrite(CLK, LOW);
}
void serialWrite(unsigned char data){
  digitalWrite(EN, LOW); //Desabilita a transferencia de dados para a saida
  
  for (unsigned char i = 0; i < 8; i++){
    digitalWrite(CLK, LOW);
    if (data & 0x80>>i){
      digitalWrite(DS, HIGH);
    }
    else{
      digitalWrite(DS, LOW);
    }
    digitalWrite(CLK, HIGH);
  }
  digitalWrite(EN, HIGH);
  digitalWrite(DS, LOW);
  digitalWrite(CLK, LOW);
  
}