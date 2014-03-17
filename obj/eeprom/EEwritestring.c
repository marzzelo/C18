#include <p18cxxx.h>					// definiciones Microchip
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	 	Lee un string desde la ram, apuntado por origen   
*                   y lo graba en la eeprom a partir de EE_BASE        													
*
* @param[in]	EE_BASE		posición de EEPROM del primer caracter a escribir.	
* @param[in]	origen		puntero al buffer de ram donde se encuentra el string a 
*							escribir, terminado en NUL
* @return					el mismo Puntero al string pasado como parámetro
*  
* @warning		\b origen debe ser un string terminado en NUL!!!!
* 																			
*******************************************************************************
* @test 
* @code	EEwritestring(EE_CALLER_ID1, CallerID);    	            @endcode
*******************************************************************************
* $Author: Mav $ $Revision: 9 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/
#if (defined(__18F4520) || defined(__18F452))
char* EEwritestring(const unsigned char EE_BASE, ram char* origen)
	{
	char i;
	for (i=0; EEwrite(EE_BASE + i, *origen++); i++);
	EEwrite(EE_BASE + i, '\0');
	return origen;
	}//


#elif (defined(__18F4620) || defined(__18F4685))
char* EEwritestring(const unsigned char page, const unsigned char EE_BASE, ram char* origen)
	{
	char i;
	for (i=0; EEwrite(page, EE_BASE + i, *origen++); i++);
	EEwrite(page, EE_BASE + i, '\0');
	return origen;
	}//


#endif

