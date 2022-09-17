/*
 * DIO.c
 *
 *  Created on: May 21, 2017
 *      Author: Eslam
 */
 /*********************************************/
  /*      Updated on 02/09/2022             */
 /********************************************/

//#include<avr/io.h>
//#include<util/delay.h>

#include<DIO.h>




                      /*********************************************************************/
                          /* Configuring the pin direction either as INPUT or OUTPUT */
                      /*********************************************************************/
DIO_STATE_t DIO_SET_PINDIRECTION(uint8_t port, uint8_t pin, uint8_t direction){
  switch(port){
         case A:{
	        if(direction==OUTPUT){// Direction: Output
	        	SET_BIT(DDRA,pin);
	              }
	        else{                // Direction Input
	        	CLR_BIT(DDRA,pin);
	               }
	        break;
            }
         case B:{
        	 if(direction==OUTPUT){// Direction: Output
        	 	SET_BIT(DDRB,pin);
        	 	              }
             else{                // Direction Input
        	 	 CLR_BIT(DDRB,pin);
        	 	        }
             break;
        	  }
         case C:{
        	 if(direction==OUTPUT){// Direction: Output
        	 	SET_BIT(DDRC,pin);
        	 	              }
        	 else{                // Direction Input
        	 	 CLR_BIT(DDRC,pin);
        	 	        }
        	  break;
        	    }
         case D:{
        	 if(direction==OUTPUT){// Direction: Output
        	 	SET_BIT(DDRD,pin);
        	 	  }
        	 else{                // Direction Input
        	 	 CLR_BIT(DDRD,pin);
        	 	 }
        	 break;
        	   }
           }
		   
		   return DIO_SUCCESS;
         }


                       /*******************************************************************************/
                          /*  In case of configuring a pin as output, send the data/bit to PINx   */
                       /*******************************************************************************/
DIO_STATE_t DIO_WRITE_PIN(uint8_t port , uint8_t pin , uint8_t pvalue){
          switch(port){
              case A:{
        	    SET_BIT(DDRA,pin);
        	    if(pvalue!=0){
        	    	SET_BIT(PORTA,pin); // Write a "1" to the pin
        	        }
        	    else{
        	    	CLR_BIT(PORTA,pin); // Write a "0" to the pin
        	        }
        	    break;
                  }
              case B:{
        	      SET_BIT(DDRB,pin);
        	      if(pvalue!=0){
        	          SET_BIT(PORTB,pin);// Write a "1" to the pin
        	          	   }
        	      else{
        	         CLR_BIT(PORTB,pin);// Write a "0" to the pin
        	          	    }
        	      break;
                   }
              case C:{
        	      SET_BIT(DDRC,pin);
        	      if(pvalue!=0){
        	           SET_BIT(PORTC,pin);// Write a "1" to the pin
        	            	   }
        	      else{
        	           CLR_BIT(PORTC,pin);// Write a "0" to the pin
        	          	   }
        	      break;
                     }
               case D:{
        	       SET_BIT(DDRD,pin);
        	       if(pvalue!=0){
        	            SET_BIT(PORTD,pin);// Write a "1" to the pin
        	          	   }
        	       else{
        	            CLR_BIT(PORTD,pin);// Write a "0" to the pin
        	          	   }
        	       break;
                    }
                  }
				  
				  return DIO_SUCCESS;
            }

            /*********************************************************************/
                /* Get the value on PINx of PORTz either it's "0" or "1" */
            /*********************************************************************/
 uint8_t DIO_READ_PIN(uint8_t port , uint8_t pin){
  uint8_t pin_data;
     switch(port){
         case A:{
            CLR_BIT(DDRA,pin);
            pin_data = PINA & (1<<pin); // Reading pin data either a "1" or "0"
            pin_data >>= pin;
            break;
              }
         case B:{
            CLR_BIT(DDRB,pin);
            pin_data = PINB & (1<<pin); // Reading pin data either a "1" or "0"
            pin_data >>= pin;
            break;
             }
          case C: {
             CLR_BIT(DDRC,pin);
             pin_data = PINC & (1<<pin); // Reading pin data either a "1" or "0"
             pin_data >>= pin;
             break;
             }
           case D:{
             CLR_BIT(DDRD,pin);
             pin_data = PIND & (1<<pin); // Reading pin data either a "1" or "0"
             pin_data >>= pin;
             break;
              }
            default: {
             pin_data = -1;
             break;
              }
        }


    return pin_data;
        }

                           /*********************************************************************/
                                   /* Configuring PORTx either as INPUT or OUTPUT */
                           /*********************************************************************/
DIO_STATE_t DIO_SET_PORTDIRECTION(uint8_t port, uint8_t direction){
	switch(port){
	          case A:{
	        	  DDRA = (direction==OUTPUT) ? 0xFF : 0x00; // Configure PORT A as Output or Input according to condition
	        	  break;
	                }
	          case B:{
                  DDRB = (direction==OUTPUT) ? 0xFF : 0x00;// Configure PORT A as Output or Input according to condition
	        	  break;
	                   }
	          case C:{
                  DDRC = (direction==OUTPUT) ? 0xFF : 0x00;// Configure PORT A as Output or Input according to condition
	        	  break;
	                    }
	          case D:{
	        	  DDRD = (direction==OUTPUT) ? 0xFF : 0x00;// Configure PORT A as Output or Input according to condition
	        	  break;
	                   }
	           default:{
	                break;
	                  }
	                }
					
					return DIO_SUCCESS;
                 }


/*********************************************************************/
         /*Function to read input from PORTx */
/*********************************************************************/
uint8_t DIO_READ_PORT(uint8_t port){
   sint8_t data = -1;
   switch(port){
         case A:{
           // By default, all ports are programmed as inputs, but also to avoid repeat changing of port
		                        //state, configure as input
           DDRA = 0x00;
           data = PINA;
           break;
            }
         case B:{
           DDRB = 0x00;
           data = PINB;
           break;
           }

          case C:{
            DDRC = 0x00;
            data = PINC;
            break;
             }

          case D:{
             DDRD = 0x00;
             data = PIND;
             break;
              }

   }
      return data;
           }


                 /*************************************************************************/
                  /*Function to send output , or transmit data in 8-bits frame via PORTx */
                 /*************************************************************************/
DIO_STATE_t DIO_WRITE_PORT(uint8_t port , uint8_t data){
   switch(port){
         case A:{
           DDRA = 0xFF;
           PORTA = data; // Send 8-bit data to PORT A
           break;
            }
         case B:{
           DDRB = 0xFF;
           PORTB = data; // Send 8-bit data to PORT B
           break;
         }
         case C:{
           DDRC = 0xFF;
           PORTC = data; // Send 8-bit data to PORT C
           break;
         }
         case D: {
           DDRD = 0xFF;
           PORTD = data; // Send 8-bit data to PORT D
           break;
         }
         default:{
            break;
          }

   }


    return DIO_SUCCESS;
 }

