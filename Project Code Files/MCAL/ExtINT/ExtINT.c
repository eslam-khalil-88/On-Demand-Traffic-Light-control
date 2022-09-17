/*
 * ExtINT.c
 *
 * Created: 11/09/2022 11:23:12
 *  Author: Eslam
 */ 


#include "ExtINT.h"
//#include <avr/interrupt.h>
#include <util/delay.h>


static uint8_t EXT_Flag = 0 , status = 0;

ISR(INT0_vect){
	
	EXT_Flag = 1;	
}

                             

/*
ISR(EXT_INT1_vect){
	
}

ISR(EXT_INT2_vect){
	
}
                           */



/**********************************************************/
           /* External Interrupt Initialization */
/**********************************************************/
ExtINT_STATE_t ExtINT_Init(uint8_t INT_PIN , uint8_t TYPE){
	
	
	switch (INT_PIN){
		// External Interrupt PIN 0
		case 0: {
			DIO_SET_PINDIRECTION(D, 2, INPUT); //Activate input state for pin
			if(TYPE == LEVEL){
				// In case of selecting low level on INT0 triggers interrupt, default value is 0
					
				//SET_BIT(MCUCR , ISC00); // Any change in logical level generates an interrupt
			}
			else{
				//SET_BIT(MCUCR , ISC00); // Falling edge generates an interrupt
				SET_BIT(MCUCR , ISC01);	
				}
			SET_BIT(GICR , INT0); // Enable INT0 Interrupt	
			
		    break;	
		}
		
		// External Interrupt PIN 1
	    case 1: {
			DIO_SET_PINDIRECTION(D, 3, INPUT); //Activate input state for pin
			if(TYPE == LEVEL){ // Level triggered interrupt
				SET_BIT(MCUCR , ISC10); // Any change in logical level generates an interrupt
			}
			else{ // falling edge triggered interrupt
				SET_BIT(MCUCR , ISC11); // Falling edge generates an interrupt
			}
			SET_BIT(GICR , INT1); // Enable INT0 Interrupt
			break;
		}
		
		// External Interrupt PIN 2
		case 2: {
			DIO_SET_PINDIRECTION(B, 2, INPUT); //Activate input state for pin
			SET_BIT(MCUCSR , ISC2); // PIN 2 is only edge triggered
			SET_BIT(GICR , INT2); // Enable INT0 Interrupt
			break;
		}
	}
	
	SET_BIT(SREG , 7); //Enabling global interrupt
	
	return ExtINT_SUCCESS;
}

/*******************************************************/
            /* Enable the interrupt */
/*******************************************************/
ExtINT_STATE_t ExtINT_ENABLE(uint8_t INT_PIN){
	switch(INT_PIN){
		case 0:{
			SET_BIT(GICR , INT0);
			break;
		}
		case 1:{
			SET_BIT(GICR , INT0);
			break;
		}
		case 2:{
			SET_BIT(GICR , INT0);
			break;
		}
	}
	
	return ExtINT_SUCCESS;
}


/*******************************************************/
               /* Disable the interrupt */
/*******************************************************/
ExtINT_STATE_t ExtINT_DISABLE(uint8_t INT_PIN){
	switch(INT_PIN){
		case 0:{
			CLR_BIT(GICR , INT0);
			break;
		}
		case 1:{
			CLR_BIT(GICR , INT0);
			break;
		}
		case 2:{
			CLR_BIT(GICR , INT0);
			break;
		}
	}
	
	return ExtINT_SUCCESS;
}
/***********************************************************/
              /* Get status of interrupt flag*/
/***********************************************************/
uint8_t GET_EXTINT_STATUS(void){
	
	
	if(EXT_Flag > 0){
			
		status = 1;
		EXT_Flag = 0;
	}                         
	
	
	return status;
}

/******************************************************************************/
    /* Clearing Status of External Interrupt to start a new interrupt case */
/******************************************************************************/
ExtINT_STATE_t CLEAR_EXTINT_STATUS(void){
	status = 0;
	
	return ExtINT_SUCCESS;
}


