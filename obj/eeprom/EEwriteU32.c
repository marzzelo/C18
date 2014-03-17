#include <p18cxxx.h>
#include "typedefs.h"					
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	Escribe un int32 en EEprom
*
* @param[in]	EEstartAddress	posición inicial de EEPROM a grabar.
* @param[in]	Int				int32_t a grabar en la posición addr.  
* @return		El mismo valor pasado como parámetro int.
* 																			
* $Author: valdez $ $Revision: 1 $ $Date: 19/12/11 10:15a $ 			
*******************************************************************************/


#if (defined(__18F4620) || defined(__18F4685))

uint32_t EEwriteU32(unsigned char page, unsigned char EEstartAddress, uint32_t Int)
{
	EEwrite(page, EEstartAddress++, (unsigned char)Int);
	EEwrite(page, EEstartAddress++, (unsigned char)(Int >> 8));
	EEwrite(page, EEstartAddress++, (unsigned char)(Int >> 16));
	EEwrite(page, EEstartAddress, (unsigned char)(Int >> 24));		
	
	return Int;
}//

#endif
//	
