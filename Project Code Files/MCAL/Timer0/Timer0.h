#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "../Utilites/stdtypes.h"
#include "../Utilites/registers.h"
#include "../MCAL/DIO/DIO.h"


#define PWM 1
#define COUNTER 0

typedef enum TIMER_STATE{
	TIMER_SUCCESS = 0,
	TIMER_FAIL
	} TIMER_STATE_t;




TIMER_STATE_t TIMER0_PWM_START(uint8_t DutyCycle , uint8_t Frequency);

TIMER_STATE_t TIMER0_DELAY(uint16_t TIME_MS);

#endif // TIMER_H_INCLUDED
