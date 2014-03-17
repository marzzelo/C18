
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

/********************************************************************
*    Function Name:  getsUART                                       *
*    Return Value:   void                                           *
*    Parameters:     buffer: pointer to string                      *
*                    len: length of characters to receive           *
*    Description:    This routine receives a string of characters   *
*                    from the USART of length specified by len.     *
********************************************************************/
char* getsUART(char *buffer, const unsigned char len)
	{
  	unsigned char i;    				// Length counter
  	unsigned char data;

  	for(i=0;i<len;i++)
		{  					// Only retrieve len characters
    	while(!PIR1bits.RCIF);				// Wait for data to be received
    	*buffer++ = data = RCREG;    	// Get a character from the USART
                           				// and save in the string
     							      	// Increment the string pointer
  		}
  	return buffer;
}//

