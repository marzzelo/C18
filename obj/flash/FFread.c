#include <p18cxxx.h>					
#include "flash.h"

#if defined(__18F4520) || defined(__18F452) || defined(__18F4620)  || defined(__18F4685)

#pragma code
/**************************************************************************//** 
* @Descripcion	Lee desde FLASH un bloque de 64 bytes de datos hacia RAM					
*
* @param[in]	address  Dirección base en la memoria de programa (FLASH)
*						 desde donde se leerán los datos.
* @param[in]	*buffer	 Puntero a un buffer destino en RAM 
* 																			
* @test
* @code			FFread(myData, 0x7C00);                                    @endcode
*
* $Author: Mav $ $Revision: 8 $ $Date: 4/12/10 2:52p $ 			
*******************************************************************************/
void FFread(unsigned char *buffer, unsigned long FFaddress)
{
	char i;
	rom unsigned char* flash_Ptr = (rom unsigned char*)FFaddress;
	
	for (i = 0; i < 64; i++)
		buffer[i] = *(flash_Ptr + i);
}//

#endif
