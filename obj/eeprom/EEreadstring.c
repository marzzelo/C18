#include <p18cxxx.h>					// definiciones Microchip
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* Descripcion:	Lee un string terminado en NUL (0x00) desde EE    
* 				y lo deposita en el buffer destino.
*
* @param[out]  	destino 	puntero a buffer de ram donde deberá entregarse el string leído desde EEPROM.		 
* @param[in]	EEORIGEN	posición de EEPROM del primer caracter del string a leer.
* @return	   				Puntero al string que se acaba de leer.
*
* @warning		Debe haber un NUL al final del string en EEPROM!!!!
*******************************************************************************
* @test 
* @code	EEreadstring(TXbuff, EE_CALLER_ID1); 					@endcode
*******************************************************************************
* $Author: Mav $ $Revision: 8 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/

#if (defined(__18F4520) || defined(__18F452))
char* EEreadstring(ram char* destino, const unsigned char EEORIGEN)
	{
	char i;
	for (i=0; *destino++ = EEread(EEORIGEN + i); i++);
	// while (*destino++ = EEread(EEBASE + i++));  // otra forma (pero inicializar char i=0)
	return destino;
	}//


#elif (defined(__18F4620) || defined(__18F4685))
char* EEreadstring(ram char* destino, const unsigned char page, const unsigned char EEORIGEN)
	{
	char i;
	for (i=0; *destino++ = EEread(page, EEORIGEN + i); i++);
	// while (*destino++ = EEread(page, EEBASE + i++));  // otra forma (pero inicializar char i=0)
	return destino;
	}//

#endif

	
