#define DS 8
#define EN 10
#define CLK 11

#define RS 7
#define E 6

void lcdInit();
void lcdCmd(unsigned char cmd);
void lcdData(unsigned char data);
void serialInit();
void serialWrite(unsigned char data);

void setup (){
 serialInit();
 lcdInit(); 

 char unifei [] = { //Valores relativos ao logo da UNIFEI
	0x01, 0x03, 0x03, 0x0E, 0x1C, 0x18, 0x08, 0x08,
	0x11, 0x1F, 0x00, 0x01, 0x1F, 0x12, 0x14, 0x1F,
	0x10, 0x18, 0x18, 0x0E, 0x07, 0x03, 0x02, 0x02,
	0x08, 0x18, 0x1C, 0x0E, 0x03, 0x03, 0x01, 0x00,
	0x12, 0x14, 0x1F, 0x08, 0x00, 0x1F, 0x11, 0x00,
	0x02, 0x03, 0x07, 0x0E, 0x18, 0x18, 0x10, 0x00
 };
 lcdCmd(0x40); //Configura para a primeira posição na memória
 for(char i=0; i<48; i++){
	lcdData(unifei[i]); //Grava cada uma das linhas em ordem
 }

 lcdCmd(0x81); //segunda coluna, primeira linha 
 lcdData(0);
 lcdData(1);
 lcdData(2);
 lcdCmd(0xC1); //segunda coluna, segunda linha 
 lcdData(3);
 lcdData(4);
 lcdData(5);
  
 lcdCmd(0x88); //nona coluna, primeira linha 
 lcdData('P');
 lcdData('Q');
 lcdData('D');
 lcdData('B');
 
 lcdCmd(0xC7); //oitava coluna, segunda linha 
 lcdData('U');
 lcdData('N');
 lcdData('I');
 lcdData('F');
 lcdData('E');
 lcdData('I'); 
  
 lcdCmd(0x0C); //Cursor desligado
 
}
void loop (){
  
}

void lcdInit(){
		
  
	pinMode(RS, OUTPUT); // Configura os pinos como saída
	pinMode(E, OUTPUT);
	digitalWrite(RS, LOW); // Inicializa com nível baixo
	digitalWrite(E, LOW);
  
  	lcdCmd(0x02); //Chaveia para o modo 4 bits
	lcdCmd(0x28) ; //4 bits, 2 linhas, 5x8
	lcdCmd(0x06) ; //modo incremental
	lcdCmd(0x0F) ; // display, cursor e blinking ON
	lcdCmd(0x03) ; // zera contadores internos
	lcdCmd(0x01) ; // limpar display
	lcdCmd(0x80) ; // posição inicial
}
void lcdCmd(unsigned char cmd){
	digitalWrite(RS, LOW); // RS = 0 para envio de comandos
	
	serialWrite(cmd);      // Escreve os 4 bits mais significativos nas porta DB7 a DB4
	digitalWrite(E, HIGH); // Pulso de clock para capturar os dados
	delayMicroseconds(40);
	digitalWrite(E, LOW);
	delayMicroseconds(40);
  
	serialWrite(cmd<<4);  // Escreve os 4 bits menos significativos nas porta DB7 a DB4
	digitalWrite(E, HIGH);// Pulso de clock para capturar os dados
	delayMicroseconds(40);
	digitalWrite(E, LOW);
	delayMicroseconds(40);
}
void lcdData(unsigned char data){
	digitalWrite(RS, HIGH); // RS = 1 para envio de dados
	
	serialWrite(data);  // Escreve os 4 bits mais significativos nas porta DB7 a DB4
	digitalWrite(E, HIGH); // Pulso de clock para capturar os dados
	delay(2);
	digitalWrite(E, LOW);
	delay(2);
	
	serialWrite(data<<4); // Escreve os 4 bits menos significativos nas porta DB7 a DB4
	digitalWrite(E, HIGH); // Pulso de clock para capturar os dados
	delay(2);
	digitalWrite(E, LOW);
	delay(2);
	digitalWrite(RS, LOW);  //Retorna RS para nível baixo
		
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
  
  for (char i = 0; i < 8; i++){
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