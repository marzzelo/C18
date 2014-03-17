/**********************************************************************
*    Processor:      P18F4550                                         *
*    Description:    UART 8n1 module control header          		  *		
**********************************************************************/

// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>


/********************************************************************
*    Function Name:  putcUART                                       *
*    Return Value:   none                                           *
*    Parameters:     data: data to transmit                         *
*    Description:    This routine transmits a byte out the USART.   *
********************************************************************/
char putcUART(const char data){
	return (TXREG = data);     	// Writes the data byte to the USART
}//

