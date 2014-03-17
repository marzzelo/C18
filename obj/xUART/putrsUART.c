
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

rom char* putrsUART(const rom char* data)
	{
  	while( *data )
  		{  // Transmit a byte
		while(!TXSTAbits.TRMT); 
		TXREG = *data++;
    	//putcUART(*data++);
  		}
  	return data;
}//

