/*
 * ExtINT.h
 *
 * Created: 11/09/2022 11:22:59
 *  Author: Eslam
 */ 


#ifndef EXTINT_H_
#define EXTINT_H_

//#include <avr/io.h>
#include "../Utilites/registers.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/Timer0/Timer0.h"


#define EDGE 0
#define LEVEL 1

typedef enum ExtINT_STATE{
	ExtINT_SUCCESS = 0,
	ExtINT_FAIL
}ExtINT_STATE_t;


ExtINT_STATE_t ExtINT_Init(uint8_t INT_PIN , uint8_t TYPE);
ExtINT_STATE_t ExtINT_ENABLE(uint8_t INT_PIN);
ExtINT_STATE_t ExtINT_DISABLE(uint8_t INT_PIN);
uint8_t GET_EXTINT_STATUS(void);
ExtINT_STATE_t CLEAR_EXTINT_STATUS(void);

#endif /* EXTINT_H_ */