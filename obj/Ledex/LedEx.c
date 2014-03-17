//+--------------------------------------------------------------------------+
//|       $Workfile:: LedEx.c                    $ $Revision:: 9             $
//+--------------------------------------------------------------------------+
//|         $Author:: Marcelo                                                $
//|        $Modtime:: 19/08/08 10:43p                                        $
//|        $Archive:: /C18/obj/Ledex/LedEx.c                                 $
//+--------------------------------------------------------------------------+

#include "ledex.h"
#include <p18cxxx.h>

/** Indica el valor a sacar por el puerto para actualizar el estado del led que está siendo 
	refrescado. Previamente debe actualizarse el registro TRIS correspondiente.  */
static rom unsigned char PLED[] = {
	
	0b00001000,
	0b00000100,
	0b00000100,
	0b00000010,
	0b00001000,
	0b00000010,
	0b00000010,
	0b00000001
};//


/** Indica el valor a setear en el registro TRIS para actualizar el estado del led que está siendo 
	refrescado. Posteriormente debe actualizarse el PUERTO correspondiente.  */	
static rom unsigned char TLED[] = {
	
	0b11110011,
	0b11110011,
	0b11111001,
	0b11111001,
	0b11110101,
	0b11110101,
	0b11111100,
	0b11111100
};//
	

#pragma code LEDEX_CODE

/**************************************************************************//** 
* @Descripcion 	Realiza el multiplexado en tiempo de leds. 
*				Controla 8 leds conectados a los pines RB<3:0>.
*				Cada led recibe un pulso de refresco de 1ms cada 7ms.
*				@par 
*				Esta rutina está diseñada para ser llamada desde ISR cada 1ms o menos.
*				Puede llamarse cada más de 1ms pero es posible que se aprecie el refresco.
*				@par 
*				El valor a mostrar en el array de 8 leds debe cargarse en una variable
*				reservada en el programa principal, del tipo unsigned char,
*				que será pasada como argumento (por valor) a esta funcion. 
*				<HR>
*
* @image 		html led_array.jpg "Circuito para 8 leds, controlado por 4 pines"
* 
* @param[in]	LEDBUFF		número a mostrar en el array de leds.
* @return		void
*  
* @warning		Probado en Pic18F452. El puerto D no es apto para esta función debido
*				a que en estado de alta impedancia permite el paso de corriente hacia masa.
* @note 
* @todo 		Generalizar para controlar N·(N-1) leds con N pines.
* @todo 		Permitir elegir el puerto y los pines.
*******************************************************************************
* @test 
* @code	        LedUpdate(LBuff);  // desde ISR para TMRn		@endcode
*******************************************************************************
* $Author: Marcelo $ $Revision: 9 $ $Date: 19/08/08 11:28p $ 			
*******************************************************************************/
void LedUpdate(BYTE LEDBUFF) {
	
	static unsigned char LedShiftPointer;  // Indica el led que está siendo refrescado en esta llamada.
	PORTB &= 0xF0;	// Apagar todos los pines que estén como OUTPUT. 
	TRISB |= 0x0F;	// llevar a HiZ todos los pines de control.
	if (LEDBUFF._byte & (1 << LedShiftPointer))	{
		
		TRISB &= TLED[LedShiftPointer]; // Llevar a OUTPUT los pines correspondientes al led que se está barriendo
		PORTB |= PLED[LedShiftPointer]; // Llevar a ON los pines correspondientes, sólo si están marcados para encender.
	
	}
	if (++LedShiftPointer > 7u) LedShiftPointer = 0;
}//


	
