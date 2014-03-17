#include <p18cxxx.h>		
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* Descripción:	- Resetea los bits EEPGD y CFGS para apuntar a la EEPROM, 
* 				- ordena la lectura mediante RD, y 
* 				- retorna el valor recuperado en EEDATA. 								
*
* @param[in]  	addr 	Posicion a leer.
* @return	   			Valor leido.
*  
*******************************************************************************
* @test 
* @code	char k = EEread(0x00); // Llamada simple	  			@endcode
* @code	for (i=0; *destino++ = EEread(EEORIGEN + i); i++);		@endcode
*																			
*******************************************************************************
* $Author: Mav $ $Revision: 13 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/
#if (defined(__18F4520) || defined(__18F452))
char EEread(unsigned char addr)
	{
	EEADR = addr;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	return EEDATA;
	}//
	


#elif (defined(__18F4620) || defined(__18F4685))
char EEread(unsigned char page, unsigned char addr)
	{
	EEADRH = page;
	EEADR = addr;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	return EEDATA;
	}//
#endif
	
