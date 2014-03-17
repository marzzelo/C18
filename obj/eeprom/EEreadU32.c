#include <p18cxxx.h>		
#include "eeprom.h"
#include "typedefs.h"

typedef union _DWORD
{
    uint32_t uint32;
    struct
    {
        unsigned char byte0;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
    };
} DWORD;   

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
* $Author: valdez $ $Revision: 2 $ $Date: 19/12/11 10:32a $ 			
*******************************************************************************/
#if (defined(__18F4620) || defined(__18F4685))

uint32_t EEreadU32(unsigned char page, unsigned char addr)
{
	DWORD Int;
	
	Int.byte0 = EEread(page, addr++);
	Int.byte1 = EEread(page, addr++);
	Int.byte2 = EEread(page, addr++);
	Int.byte3 = EEread(page, addr);
		
	return Int.uint32;
}//



#endif

