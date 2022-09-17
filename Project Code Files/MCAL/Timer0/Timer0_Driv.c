/*
Created: 27/07/2017
Author: Eslam
   Updated: 09/09/2022
*/

//#include <avr/io.h>
//#include <avr/interrupt.h>
#include "Timer0.h"


static uint8_t OVF_flag = 0;

/*
ISR (TIMER0_COMP_vect){

   }                        */


ISR (TIMER0_OVF_vect){
	OVF_flag = 1;
}                   
/****************************************************************************/
/* Generating a delay using counter mode in case of using clk: 1MHz */
/****************************************************************************/
TIMER_STATE_t TIMER0_DELAY(uint16_t TIME_MS){
	uint16_t count;
	f32_t ct ;
	f32_t overflow_cyc;
	
	if(TIME_MS <= 2){
		TCCR0 = (1<<CS01);
		ct = (TIME_MS * 1000) / 8;
		OCR0 = ct;
		SET_BIT(SREG , 7);
		SET_BIT(TIMSK , OCIE0);
		while((TIFR &= 2) == 0);
		CLR_BIT(TIFR , 1);
		CLR_BIT(TIMSK , OCIE0);
		//Stop the timer
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);
	}
	else if(TIME_MS > 2 && TIME_MS <= 16){
		TCCR0 = (1<<CS01) | (1<<CS00);
		ct = (TIME_MS * 1000) / 64;
		OCR0 = ct;
		SET_BIT(SREG , 7);
		SET_BIT(TIMSK , OCIE0);
		while((TIFR &= 2) == 0);
		CLR_BIT(TIFR , 1);
		CLR_BIT(TIMSK , OCIE0);
		//Stop the timer
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);
	}
	
	else if(TIME_MS > 16 && TIME_MS <= 65){
		TCCR0 = (1<<CS02);
		ct = (TIME_MS * 1000) / 256;
		OCR0 = ct;
		SET_BIT(SREG , 7);
		SET_BIT(TIMSK , OCIE0);
		while((TIFR &= 2) == 0);
		CLR_BIT(TIFR , 1);
		CLR_BIT(TIMSK , OCIE0);
		//Stop the timer
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);
		
	}
	else{
		//TCCR0 = (1<<CS00) | (1<<CS02);
		SET_BIT(TCCR0 , CS00);
		SET_BIT(TCCR0 , CS02);
		//Use the global variable count to count number of overflow cycles
		ct = (TIME_MS * 1000.0) / 1024.0;
		overflow_cyc = ct / 256.0;
		count = (uint16_t) overflow_cyc;
		SET_BIT(SREG , 7);
		SET_BIT(TIMSK , TOIE0);
		
		while(count > 0){
			//SET_BIT(SREG , 7);
			//SET_BIT(TIMSK , TOIE0);
			
			//OCR0 = 255;
			while(OVF_flag == 0);
			OVF_flag = 0;
			count--;
		}
		//CLR_BIT(SREG , 7);
		//Stop the timer
		CLR_BIT(TCCR0 , CS00);
		CLR_BIT(TCCR0 , CS01);
		CLR_BIT(TCCR0 , CS02);
	}
	
	
	return TIMER_SUCCESS;
}



/****************************************************************************/
          /* Start Timer 0 as a PWM Signal Generator   */
/****************************************************************************/
TIMER_STATE_t TIMER0_PWM_START(uint8_t DutyCycle , uint8_t Frequency){
  f32_t duty = (f32_t) DutyCycle;
  duty = ((duty) / 100.0) * 256.0;
  OCR0 = (uint16_t) duty;
  SET_BIT(SREG , 7);
  SET_BIT(TIMSK , OCIE0);
  
  return TIMER_SUCCESS;
     }


