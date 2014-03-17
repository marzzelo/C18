#include <p18cxxx.h>					
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* @Descripcion	Antes de habilitar la escritura, resetea los bits 
*               @b EEPGD y @b CFGS para apuntar a la memoria EEPROM,    
*               Luego deshabilita las interrupciones, genera la   
*               secuencia de seguridad 55/AA, ordena la escritura 
*               con WR=1, y habilita nuevamente las interrupciones
*               Espera la bajada de WR por hardware y deshabilita 
*               la escritura por seguridad.						
*
* @param[in]	addr	posición de EEPROM a grabar.
* @param[in]	value	valor a grabar en la posición addr.  
* @return		El mismo valor pasado como parámetro value.
* 																			
* @test
* @code			EEwrite(0x00, 0x28);                                        @endcode
* @code			for (i=0; EEwrite(EE_BASE + i, *origen++); i++);            @endcode															
*
* $Author: valdez $ $Revision: 10 $ $Date: 17/09/13 15:23 $ 			
*******************************************************************************/

#if (defined(__18F4520) || defined(__18F452))
char EEwrite(unsigned char addr, unsigned char value)
{
	EEADR = addr;
	EEDATA = value;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	
	INTCONbits.GIE = 0;
	EECON2 = 0X55;
	EECON2 = 0XAA;
	
	EECON1bits.WR = 1;
	INTCONbits.GIE = 1;
	
	while (EECON1bits.WR);
	EECON1bits.WREN = 0;
	return value;
}//
	
#elif (defined(__18F4620) || defined(__18F4685) || defined(__18F8722))
char EEwrite(unsigned char page, unsigned char addr, unsigned char value)
{
	EEADRH = page;
	EEADR = addr;
	EEDATA = value;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	
	INTCONbits.GIE = 0;
	EECON2 = 0X55;
	EECON2 = 0XAA;
	
	EECON1bits.WR = 1;
	INTCONbits.GIE = 1;
	
	while (EECON1bits.WR);
	EECON1bits.WREN = 0;
	return value;
}//

#endif


	
