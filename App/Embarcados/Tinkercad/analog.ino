#define BUZZER 9
#define LM A0
#define LDR A1
#define POT A2

void setup(){
  pinMode(BUZZER, OUTPUT); //Configura a porta como saída
  pinMode(LM, INPUT); //Configura as portas como entrada
  pinMode(LDR, INPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600); //Inicializa a comunicação serial
}

void loop(){
  static unsigned long info = 0;
  
  if (millis() - info > 200){ //É executado 200ms após o reset da variável info
    info = millis(); //Reseta a variável info
    
  	Serial.print("Temp = ");
  	Serial.print(map(analogRead(LM),0, 1023, -50, 450)); 	// Converte 0 a 1023 em -50ºC a 450ºC
  	Serial.println("oC");
	  
  	Serial.print("LDR = ");
	Serial.println(analogRead(LDR)); //Imprime o valor sem conversão da leitura analógica
	  
  	Serial.print("Potenciometro = ");
  	Serial.print(map(analogRead(LM),0, 1023, 0, 100));	// Converte 0 a 1023 em 0% a 100%
  	Serial.println("% \n");
  }
  if(analogRead(POT)>128){
    static unsigned long timeBuzz = 0;
    if(millis() - timeBuzz > 100){	//É executado 100ms após o reset da variável timeBuzz
  	   tone(BUZZER, 100 + analogRead(POT)); // Liga o buzzer com uma frequência dependente do valor do potenciômetro
    }
    if(millis() - timeBuzz > 300){  //É executado 300ms após o reset da variável timeBuzz
       noTone(BUZZER);	//Desliga o BUZZER
       timeBuzz = millis(); //Reseta a variável timeBuzz
    }
  }
  else{
    noTone(BUZZER);
  }
}
