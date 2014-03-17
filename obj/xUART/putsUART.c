/**********************************************************************
*    Processor:      P18F4550                                         *
*    Description:    UART 8n1 module control header          		  *		
**********************************************************************/

// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

/**********************************************************************
*    Function Name:  putsUART                                         *
*    Return Value:   void                                             *
*    Parameters:     data: pointer to string of data                  *
*    Description:    This routine transmits a string of characters    *
*                    to the USART NOT including the null.             *
*	 Example:	 	 ram char MyString[] = "Hola mundo!";			  *
*					 putsUART(MyString);							  *
**********************************************************************/
char* xputsUART(const ram char* dato)
	{
  	while( *dato )
		{  // Transmit a byte
		while(!TXSTAbits.TRMT); 
		TXREG = *dato++;
		//putcUART(*data++);
		} 
  	return dato;
	}//
//

