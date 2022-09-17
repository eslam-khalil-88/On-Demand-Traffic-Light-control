/*
 * LED.c
 *
 * Created: 09/09/2022 21:18:20
 *  Author: Eslam Khalil
 */ 

#include "LED.h"



void LED_Init(void){
	DIO_SET_PORTDIRECTION(A, OUTPUT);
	DIO_SET_PINDIRECTION(D, 7, OUTPUT);
}

void LED_ON(uint8_t PORT , uint8_t PIN){
	DIO_SET_PINDIRECTION(PORT, PIN, OUTPUT);
	DIO_WRITE_PIN(PORT , PIN , 1);
}

void LED_OFF(uint8_t PORT , uint8_t PIN){
	DIO_SET_PINDIRECTION(PORT, PIN, OUTPUT);
	DIO_WRITE_PIN(PORT , PIN , 0);
}

// Blink a LED for 1-seconds
void LED_Blink(uint8_t PORT , uint8_t PIN){
	uint8_t ct = 2;
	while(ct > 0){
		if(ct%2 == 0){
			LED_ON(PORT , PIN);
			TIMER0_DELAY(500);
		}
		else{
			LED_OFF(PORT , PIN);
			TIMER0_DELAY(500);
		}
		ct--;
	}
}

// Blink 2 LEDs for 5-seconds interval
void Double_LED_Blink(uint8_t PORT_1 , uint8_t PIN_1 , uint8_t PORT_2 , uint8_t PIN_2){
	uint8_t ct = 10;
	DIO_SET_PINDIRECTION(A, 6, OUTPUT);
	DIO_SET_PINDIRECTION(A, 1, OUTPUT);
	while(ct > 0){
		if(ct%2 == 0){
			LED_ON(PORT_1 , PIN_1);
			LED_ON(PORT_2 , PIN_2);
			TIMER0_DELAY(500);
		}
		else{
			LED_OFF(PORT_1 , PIN_1);
			LED_OFF(PORT_2 , PIN_2);
			TIMER0_DELAY(500);
		}
		ct--;
	}
}