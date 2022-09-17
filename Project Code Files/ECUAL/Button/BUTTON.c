/*
 * BUTTON.c
 *
 * Created: 09/09/2022 21:38:01
 *  Author: Eslam
 */
#include "BUTTON.h" 

void BUTTON_init(uint8_t PORT , uint8_t PIN){
	DIO_SET_PINDIRECTION(PORT, PIN, INPUT);
}

uint8_t BUTTON_Read(uint8_t PORT , uint8_t PIN){
	//uint8_t val = DIO_READ_PIN(PORT , PIN);
	
	uint8_t val = GET_EXTINT_STATUS();
	
	return val;
}