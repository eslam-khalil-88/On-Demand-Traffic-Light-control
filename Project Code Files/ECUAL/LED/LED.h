/*
 * LED.h
 *
 * Created: 09/09/2022 21:18:07
 *  Author: Eslam Khalil
 */ 


#ifndef LED_H_
#define LED_H_

#include "stdtypes.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/Timer0/Timer0.h"

void LED_Init(void);
void LED_ON(uint8_t PORT , uint8_t PIN);
void LED_OFF(uint8_t PORT , uint8_t PIN);
void LED_Blink(uint8_t PORT , uint8_t PIN);
void Double_LED_Blink(uint8_t PORT_1 , uint8_t PIN_1 , uint8_t PORT_2 , uint8_t PIN_2);


#endif /* LED_H_ */