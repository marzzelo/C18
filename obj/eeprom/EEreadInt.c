#include <p18cxxx.h>		
#include "eeprom.h"

typedef union _WORD
{
    int int0;
    struct
    {
        unsigned char byte0;
        unsigned char byte1;
    };
} WORD;   

#pragma code 
/**************************************************************************//** 
* Descripción:	Lee un int desde EEprom								
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
* $Author: Mav $ $Revision: 8 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/

#if (defined(__18F4520) || defined(__18F452))
int EEreadInt(unsigned char addr)
{
	WORD Int;
	
	Int.byte0 = EEread(addr++);
	Int.byte1 = EEread(addr);
		
	return Int.int0;
}//


	
#elif (defined(__18F4620) || defined(__18F4685))
int EEreadInt(unsigned char page, unsigned char addr)
{
	WORD Int;
	
	Int.byte0 = EEread(page, addr++);
	Int.byte1 = EEread(page, addr);
		
	return Int.int0;
}//

unsigned int EEreadUInt(unsigned char page, unsigned char addr)
{
	WORD Int;
	
	Int.byte0 = EEread(page, addr++);
	Int.byte1 = EEread(page, addr);
		
	return (unsigned int)Int.int0;
}//

#endif

