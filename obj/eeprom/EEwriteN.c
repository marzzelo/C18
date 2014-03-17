#include <p18cxxx.h>					
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	Copia a EEprom el contenido de un buffer en RAM. 
*			    Debe hacerse casting del buffer a const char* si es necesario.
*
* @param[in]	EEstartAddress	posición inicial de EEPROM a grabar.
* @param[in]	ramBuff			Buffer con los caracteres a grabar en la posición addr.  
* @param[in]	n				cantidad de caracteres a grabar.
* @return		El mismo valor pasado como parámetro ramBuff.
* 																			
* @test
* @code			EEwriteN(EE_CALLER_ID0, (const char*)&aPacked2, sizeof aPacked2);    @endcode
*
* $Author: Mav $ $Revision: 6 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/

#if (defined(__18F4520) || defined(__18F452))
char* EEwriteN(unsigned char EEstartAddress, const char* ramBuff, unsigned char n)
{
	unsigned char i;

	for (i = 0; i < n; i++)
		EEwrite(EEstartAddress++, ramBuff[i]);
	
	return ramBuff;
}//


#elif (defined(__18F4620) || defined(__18F4685))
char* EEwriteN(unsigned char page, unsigned char EEstartAddress, const char* ramBuff, unsigned char n)
{
	unsigned char i;

	for (i = 0; i < n; i++)
		EEwrite(page, EEstartAddress++, ramBuff[i]);
	
	return ramBuff;
}//

#endif

	
