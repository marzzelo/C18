
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

/********************************************************************
*    Function Name:  getnUART                                       *
*    Return Value:   el mismo buffer pasado como parametro          *
*    Parameters:     buffer: pointer to string                      *
*                    len: length of characters to receive           *
*    Description:    This routine receives a set of characters      *
*                    from the USART of length specified by len.     *
********************************************************************/
char* getnUART(char *buffer, int len)
{
  	char i;    							// Length counter


  	for(i=0;i<len;i++)
	{  									// Only retrieve len characters
    	while(!PIR1bits.RCIF);			// Wait for data to be received
    	*buffer++ = RCREG;    			// Get a character from the USART
                           				// and save in the string
     							      	// Increment the string pointer
	}
  	return buffer;
}//

