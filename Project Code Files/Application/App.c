/*
 * App.c
 *
 * Created: 12/09/2022 18:03:14
 *  Author: Eslam
 */ 
#include "App.h"

void App_Start(){
                                /* Initialization for peripherals and DIO*/
    BUTTON_init(D , 2);// Initializing button by selecting the port and pin to use
    LED_Init(); // Initialize LEDs to be used by specifying selecting direction of pins
    ExtINT_Init(0 , LEVEL); // Initialize external interrupt selecting the pin, and type of interrupt
    uint8_t PREV_color , CURRENT_color;
    uint8_t seconds;
	
	//DIO_SET_PINDIRECTION(D, 5, OUTPUT); //Debugging
    
                                       /***  Main Application  ***/
    while (1)
    {
	    PREV_color = YELLOW; //Holds previous color transition
	    CURRENT_color = RED;//Holds current color
	    seconds = 5;
	    //light_contrl = RED; // GREEN for pedestrian , RED for cars
	    
	    /***************************************************************/
	                         /* Normal Mode */
	    /***************************************************************/
	    while(BUTTON_Read(D , 2) == NORMAL_MODE){
		    if(PREV_color == YELLOW && CURRENT_color == RED){
			    // In case 5-seconds is not over yet
			    if(seconds > 0){
				    LED_ON(A , 0);
				    TIMER0_DELAY(1000);//1000 ms timer delay
					
				    seconds--;
			    }
			    // When 5-seconds are over
			    else{
				    LED_OFF(A , 0);
				    seconds = 5;
				    PREV_color = RED; // Input next case, where current color is "YELLOW" and previous is "RED"
				    CURRENT_color = YELLOW;
				    continue;
			    }
		    }
		    
		    // Second case from RED to YELLOW
		    else if(PREV_color == RED && CURRENT_color == YELLOW){
			    if(seconds > 0){
				    LED_ON(A , 1);
				    //TIMER0_DELAY(1000);//1000 ms
				    
				    LED_Blink(A , 1);
				    seconds--;
			    }
			    // When 5-seconds are over
			    else{
				    LED_OFF(A , 1);
				    seconds = 5;
				    PREV_color = YELLOW;
				    CURRENT_color = GREEN;
				    continue;
			    }
		    }
		    
		    // Third case from YELLOW to GREEN
		    else if(PREV_color == YELLOW && CURRENT_color == GREEN){
			    if(seconds > 0){
				    LED_ON(A , 2);
				    TIMER0_DELAY(1000);//1000 ms
				    seconds--;
			    }
			    // When 5-seconds are over
			    else{
				    LED_OFF(A , 2);
				    seconds = 5;
				    PREV_color = GREEN;
				    CURRENT_color = YELLOW;
				    continue;
			    }
		    }
		    //Fourth case from GREEN to YELLOW
		    else if(PREV_color == GREEN && CURRENT_color == YELLOW){
			    if(seconds > 0){
				    LED_ON(A , 1);
				    //TIMER0_DELAY(1000);//1000 ms
				    LED_Blink(A , 1);
				    seconds--;
			    }
			    // When 5-seconds are over
			    else{
				    LED_OFF(A , 1);
				    seconds = 5;
				    PREV_color = YELLOW;
				    CURRENT_color = RED;
				    continue;
			    }
		    }
		    //Fifth case from YELLOW to RED
		    else{
			    if(seconds > 0){
				    LED_ON(A , 0);
				    TIMER0_DELAY(1000);//1000 ms
				    seconds--;
			    }
			    // When 5-seconds are over
			    else{
				    LED_OFF(A , 0);
				    seconds = 5;
				    PREV_color = RED;
				    CURRENT_color = YELLOW;
				    continue;
			    }
		    }
		    
		    //end of all if-conditions
	    }
	    
	    
	    
	    /***************************************************************/
	    /* Pedestrian Mode */
	    /***************************************************************/
	    while(BUTTON_Read(D , 2) == PED_MODE){
		    // In case Car's light is RED, pedestrians is green and allowed to pass
			
		    if(PREV_color == YELLOW && CURRENT_color == RED){
			    LED_ON(A , 0);//Red light for cars
			    LED_ON(A , 7);//Green light for pedestrians
			    
			    ExtINT_DISABLE(0);//Disable external interrupt to avoid repeated interrupts
			    
			    TIMER0_DELAY(5000);//count 5 seconds
			    PREV_color = RED;
			    CURRENT_color = YELLOW;
			    LED_OFF(A , 0);//Red light for cars
			    LED_OFF(A , 7);//Green light for pedestrians
			    //DIO_WRITE_PIN(D,5,1);
		    }
		    
		    // In case Car's light is yellow and going to be green, both must be yellow
		    else if(PREV_color == RED && CURRENT_color == YELLOW){
			    //LED_ON(A , 1);//Yellow light for cars
			    //LED_ON(A , 6);//Yellow light for pedestrians
			    
			    ExtINT_DISABLE(0);//Disable external interrupt to avoid repeated interrupts
			    
			    //TIMER0_DELAY(5000);//count 5 seconds
			    Double_LED_Blink(A , 1 , A , 6);
			    CURRENT_color = GREEN;
			    PREV_color = YELLOW;
			    LED_OFF(A , 1);//Turn off Red light for cars
			    LED_OFF(A , 6);//Turn off Green light for pedestrians
			    continue;
		    }
		    
		    // In case Car's light is Green, pedestrians must be Red and wait till Car's led is RED
		    else if(PREV_color == YELLOW && CURRENT_color == GREEN){
			    LED_ON(A , 2);//Green light for cars
			    LED_ON(A , 5);//Red light for pedestrians
			    
			    ExtINT_DISABLE(0);//Disable external interrupt to avoid repeated interrupts
			    
			    TIMER0_DELAY(5000);//count 5 seconds
			    CURRENT_color = YELLOW;
			    PREV_color = GREEN;
			    LED_OFF(A , 2);//Turn off Green light for cars
			    LED_OFF(A , 5);//Turn off Red light for pedestrians
			    continue;
		    }
		    // In case Car's light is Yellow, and is going to be Green after 5-seconds, both must be Yellow and
		    // pedestrian to be ready to pass
		    else if (PREV_color == GREEN && CURRENT_color == YELLOW){
			    //LED_ON(A , 1);//Yellow light for cars
			    //LED_ON(A , 6);//Yellow light for pedestrians
			    
			    ExtINT_DISABLE(0);//Disable external interrupt to avoid repeated interrupts
			    
			    //TIMER0_DELAY(5000);//count 5 seconds
			    Double_LED_Blink(A , 1 , A , 6);
			    CURRENT_color = RED;
			    PREV_color = YELLOW;
			    LED_OFF(A , 1);//Turn off Yellow light for cars
			    LED_OFF(A , 6);//Turn off Yellow light for pedestrians
			    continue;
		    }
		    else{
			    //Nothing
		    }
		    
		    
		    
		    // At the end, clear the button state to start a new normal mode and turn off all pedestrian LEDs
		    TIMER0_DELAY(500); // Delay to avoid changing state in short time
		    CLEAR_EXTINT_STATUS();
		    ExtINT_ENABLE(0); // Re-enable external interrupt again
		    LED_OFF(A , 5);
		    LED_OFF(A , 6);
		    LED_OFF(A , 7);
		    break;
	    }
	    
    }


}