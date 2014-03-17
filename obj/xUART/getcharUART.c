
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

char getcharUART(void){
  while(!PIR1bits.RCIF);	// Wait for data to be received
  return RCREG;    			// Get a character from the USART
  }//

