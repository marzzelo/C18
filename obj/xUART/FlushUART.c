#include <p18cxxx.h>

/**************************************************************************//** 
* @Descripcion 	Resetea la logica de recepcion para el caso de que un error
*				overflow bloquee el puerto serial. S/ recomendacion Microchip.
* 
* @param[in]	void
* @return		void
*  
* @warning		El bucle while no retorna hasta que la flag RCIF sea nula.
* @todo 		Contemplar WDT
*******************************************************************************
* @test 
* @code		FlushUART();                                   	            @endcode
*******************************************************************************
* $Author: Marcelo $ $Revision: 4 $ $Date: 15/11/07 1:50p $ 			
*******************************************************************************/
void FlushUART(void)
	{
	unsigned char dummy;	
	RCSTAbits.CREN = 0; 
	RCSTAbits.CREN = 1;
	while (PIR1bits.RCIF) 
		dummy = RCREG;
	}//
