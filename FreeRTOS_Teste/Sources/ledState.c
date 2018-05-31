#include "ledState.h"

static uint8_t state = 0;

void setState(uint8_t value){
	state = value;
}

uint8_t getState(){
	return state;
}
