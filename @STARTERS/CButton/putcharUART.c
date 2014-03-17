
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>

/********************************************************************
*    Function Name:  putcharUART                                    *
*    Return Value:   el mismo char pasado como parámetro            *
*    Parameters:     a: caracter a escribir                         *
*    Description:    Envia un caracter a la UART, verificando       *
*                    previamente que no haya transmision en curso.  *
********************************************************************/
char putcharUART(char a)
{
	while(!TXSTAbits.TRMT); 
	TXREG = a;
	return a;
}//

