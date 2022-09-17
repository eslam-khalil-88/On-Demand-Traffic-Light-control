/*
 * BUTTON.h
 *
 * Created: 09/09/2022 21:37:49
 *  Author: Eslam
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdtypes.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ExtINT/ExtINT.h"

void BUTTON_init(uint8_t PORT , uint8_t PIN);
uint8_t BUTTON_Read(uint8_t PORT , uint8_t PIN);



#endif /* BUTTON_H_ */