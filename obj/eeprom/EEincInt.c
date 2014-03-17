#include <p18cxxx.h>					
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	Incrementa un int en EEprom
*
* @param[in]	EEstartAddress	posición inicial de EEPROM a grabar.
* @param[in]	value			valor en que se debe incrementar el EEInt
* @return		El resultado grabado en EEprom
* 																			
* @test
* @code			EEincInt(EE_VALUE, 3);    @endcode
*
* $Author: Mav $ $Revision: 2 $ $Date: 24/12/10 5:46p $ 			
*******************************************************************************/


#if (defined(__18F4620) || defined(__18F4685))
int EEincInt(unsigned char page, unsigned char EEstartAddress, int value)
{
	int Int;
	Int = EEreadInt(page, EEstartAddress);
	EEwriteInt(page, EEstartAddress, ++Int);
	return Int;
}//

unsigned int EEincUInt(unsigned char page, unsigned char EEstartAddress, unsigned int value)
{
	unsigned int UInt;
	UInt = EEreadUInt(page, EEstartAddress);
	EEwriteUInt(page, EEstartAddress, ++UInt);
	return UInt;
}//


#endif
//	
