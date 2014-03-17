#include <p18cxxx.h>					
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	Escribe un int en EEprom
*
* @param[in]	EEstartAddress	posición inicial de EEPROM a grabar.
* @param[in]	ramBuff			Buffer con los caracteres a grabar en la posición addr.  
* @param[in]	n				cantidad de caracteres a grabar.
* @return		El mismo valor pasado como parámetro ramBuff.
* 																			
* @test
* @code			EEwriteN(EE_CALLER_ID0, (const char*)&aPacked2, sizeof aPacked2);    @endcode
*
* $Author: valdez $ $Revision: 9 $ $Date: 17/09/13 15:23 $ 			
*******************************************************************************/

#if (defined(__18F4520) || defined(__18F452))
int EEwriteInt(unsigned char EEstartAddress, int Int)
{

	EEwrite(EEstartAddress++, (char)Int);
	EEwrite(EEstartAddress, (char)(Int >> 8));
	
	return Int;
}//

#elif (defined(__18F4620) || defined(__18F4685) || defined(__18F8722))
int EEwriteInt(unsigned char page, unsigned char EEstartAddress, int Int)
{

	EEwrite(page, EEstartAddress++, (char)Int);
	EEwrite(page, EEstartAddress, (char)(Int >> 8));
	
	return Int;
}//

unsigned int EEwriteUInt(unsigned char page, unsigned char EEstartAddress, unsigned int Int)
{

	EEwrite(page, EEstartAddress++, (unsigned char)Int);
	EEwrite(page, EEstartAddress, (unsigned char)(Int >> 8));
	
	return (unsigned int)Int;
}//

#endif
//	
