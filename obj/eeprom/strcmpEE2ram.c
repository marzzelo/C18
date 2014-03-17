#include <p18cxxx.h>					// definiciones Microchip
#include "eeprom.h"

#pragma code
/**********************************************************************
*    Function Name: strcmpEE2ram                                      *
*    Return Value:  0 si los strings son iguales, 1 si son distintos  *
*    Parameters:    strram: puntero a un string terminado en NUL      *
*					alojado en RAM.									  *
*					strEE: Dirección base de un string en EEprom	  *
*    Description:   Se compara hasta encontrar el 0 en el string      *
*					ubicado en ram, o hasta detectar la primera 	  *
*					diferencia.										  *
*                                                                     *
*	 Example:	 	if (!strcmpEE2ram(rambuf, 0x00)) {...} 		      *
**********************************************************************/

/**************************************************************************//** 
* @Descripcion	Se compara hasta encontrar el \b 0 en el string 
*				ubicado en \b ram, o hasta detectar la primera
*				diferencia.													
* 
* @param[in]	strram	puntero a un string terminado en \b NUL alojado en RAM
* @param[in]	strEE	Dirección base de un string en EEprom
* @return		\b 0 si los strings son iguales, \b 1 si son distintos
*  
*******************************************************************************
* @test 
* @code	 if (!strcmpEE2ram(rambuf, 0x00)) {...} 						@endcode													
*******************************************************************************
* $Author: Mav $ $Revision: 8 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/


#if (defined(__18F4520) || defined(__18F452))
char strcmpEE2ram(const char * strram, const unsigned char strEE )
{
	char EEbase = strEE;
	while (*strram)	if (EEread(EEbase++) != *strram++)	return 1;
	return 0;
}//
	

#elif (defined(__18F4620) || defined(__18F4685))
char strcmpEE2ram(const char * strram, const unsigned char page, const unsigned char strEE )
{
	char EEbase = strEE;
	while (*strram)	if (EEread(page, EEbase++) != *strram++)	return 1;
	return 0;
}//
	
#endif


