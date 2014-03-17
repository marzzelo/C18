//+--------------------------------------------------------------------------+
//|  $Workfile:: isr_Template.c                          $ $Revision:: 1     $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 28/09/10 8:03p                                               $
//|  $Archive:: /@CODE/SRC/Templates/isr_Template.c                          $
//+--------------------------------------------------------------------------+

/*************************************************************************//**
@file 	            
@brief	                                                                             
 ****************************************************************************/
#include <p18cxxx.h>
#include <typedefs.h>		 	 			/* MAV: tipos definidos uso comun */
#include "main.h"


void ISRH(void);    
void ISRL(void);    

//+--------------------------------------------------------+
//| Vector de interrupciones de ALTA PRIORIDAD             |
//+--------------------------------------------------------+
#pragma code ISRH_CODE = 0x8			// Ubicar los gotos en 0x0008 (High Int)
void high_vector() 
{
	_asm 
		goto ISRH 
	_endasm									
}//

//+--------------------------------------------------------+
//| Vector de interrupciones de BAJA PRIORIDAD             |
//+--------------------------------------------------------+
#pragma code ISRL_CODE = 0x18
void low_vector() 
{
  	_asm 
		goto ISRL 							
	_endasm
}//



/*..........................................................................*/
#pragma code
#pragma interrupt ISRH
void ISRH(void) {
	if(PIR1bits.TMR1IF)
	{
		PIR1bits.TMR1IF = 0;		
		
        TMR1H = (uint8_t)(SYSTEM_TICK_TOUT >> 8);
        TMR1L = (uint8_t)(SYSTEM_TICK_TOUT);
  
  		/////////////////////////////////////////////////
  		////////////////<< 10 ms Start >>////////////////
  		///////////////////////////////////////////////// 
  
        QF_tick();                      /* handle all armed time events in QF */
                      
        ////////////////<< 10 ms End   >>////////////////
	} 	
	
	else if (INTCONbits.TMR0IF)
	{
		/***********************************************
		 *                  T M R 0                    *
		 ***********************************************/
		INTCONbits.TMR0IF = 0;

        TMR0L = (uint8_t)(SYSTEM_T0_TOUT);
        TMR0H = (uint8_t)((SYSTEM_T0_TOUT) >> 8);
		
		/////////////////////////////////////////////////
		////////////////<<  1 ms Start >>////////////////
		/////////////////////////////////////////////////

		RxUart_TOut_ISR();			 /* Enviar señal de time-Out a RxUart FSM */
		
		FSMLed_refresh(leds);				    /* Barrido permanente de leds */
		
		if (RCSTA & 0b00000110) 			      /* FRAME or OVERFLOW ERRORS */
		{
			RCSTAbits.CREN = 0;
			RCSTAbits.CREN = 1;
			PIE1bits.RCIE = 1;
		}

		////////////////<< 1 ms End    >>//////////////// 
	}
	
	
	
	
	/***********************************************
	 *                 R X U A R T                 *
	 ***********************************************/
	else if (PIR1bits.RCIF) 
	{  	
		RxUart_ISR();							/* Enviar caracter a la FSM */
	}	
	
	
	else if (PIR1bits.TXIF)
	{
		// Informar transmision finalizada -->
		PIE1bits.TXIE = 0;
	}
}

#pragma interrupt ISRL
void ISRL(void) 
{
}
	
/*..........................................................................*/

