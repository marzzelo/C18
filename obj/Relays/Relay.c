//+--------------------------------------------------------------------------+
//|  $Workfile:: Relay.c                           $ $Revision:: 9           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 20/09/13 10:03                                               $
//|  $Archive:: /@C18/SRC/LATCH2/Relay.c                                     $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "Relay.h"
#include <stdio.h>

#define NASSERT

DEFINE_THIS_FILE;

Relay *Relay_ctor(Relay *me, 
				  uint8_t id,
				  uint16_t Ton, 
				  uint16_t Toff,
				  uint16_t offset,
				  uint16_t cycles,
				  RelayHandler onStartTon,
				  RelayHandler onStartToff,
				  RelayHandler onCyclesCompleted,
				  BOOL startsHI)
{
	me->_id = id;
	me->_Ton = Ton;
	me->_Toff = Toff;
	me->_offset = offset;
	me->_cycles = cycles;
	me->_t = 0;				// stopped;
	me->_c = 0;

	me->_ENABLED = FALSE;
	me->_PAUSED = FALSE;
	me->_STARTS_HI = startsHI;
	
	me->_onStartTon = onStartTon;
	me->_onStartToff = onStartToff;
	me->_onCyclesCompleted = onCyclesCompleted;
	
	me->_state = IDLE;
	return me;
} //


void Relay_cstart(Relay *me, uint16_t inicnt, uint16_t coffset) // custom start
{
	ASSERT(me->_Ton > 0); 	/* ERROR: se ha instanciado el objeto? */
	ASSERT(me->_Toff > 0);	/* ERROR: se ha instanciado el objeto? */
	
	if (!me->_Ton || !me->_Toff) {
		me->_ENABLED = FALSE;
		return;
	}	
		
	me->_c = me->_cycles - inicnt;
	me->_t = coffset; // me->_offset;
	me->_state = DELAYING;
	me->_PAUSED = FALSE;
}//


void Relay_stop(Relay *me)
{
	me->_t = 0;
	me->_state = IDLE;
}//


void Relay_pause(Relay *me)
{
	me->_PAUSED = TRUE;
}//

void Relay_resume(Relay *me)
{
	me->_PAUSED = FALSE;
}//


// Colocar en ISR de algún timer (ej.: 1ms)
void Relay_update(Relay *me)
{
	ASSERT(me->_Ton > 0); 	/* ERROR: se ha instanciado el objeto? */
	ASSERT(me->_Toff > 0);	/* ERROR: se ha instanciado el objeto? */

	if (!me->_ENABLED)
		return;
		
	if (me->_PAUSED)
		return;

	if (!me->_Ton || !me->_Toff)
		return;
				
	switch (me->_state) {
		case IDLE:
			break;
			
		case DELAYING:
			if (me->_t == 0) {
				if (me->_STARTS_HI) {
					me->_t = me->_Ton;
					if (me->_onStartTon != null) 	// evitar null pointer
						me->_onStartTon(me->_id); 	// si llegó a 0, lanzar evento
					me->_state = COUNTING_ON;
				}
				else {
					me->_t = me->_Toff;
					if (me->_onStartToff != null) 	// evitar null pointer
						me->_onStartToff(me->_id); 	// si llegó a 0, lanzar evento
					me->_state = COUNTING_OFF;
				}
			}
			else
				--me->_t;							// continuar con el offset
			
			break;
			
counting_on:			
		case COUNTING_ON:
			if (me->_t)	{
				if (!--me->_t) {  					// decrementar t restante
					if (me->_onStartToff != null) 	// evitar null pointer
						me->_onStartToff(me->_id); 	// si llegó a 0, lanzar evento
					
					if (me->_c) {				// si se especificó #of cycles...
						if (!--me->_c) {
										// contar
							if (me->_onCyclesCompleted != null) 
								me->_onCyclesCompleted(me->_id);	// avisar
							me->_state = IDLE;		
							break;
						}
					}	
					
					me->_t = me->_Toff;	
					me->_state = COUNTING_OFF;						
				}
			}
			break;
			
counting_off:		
		case COUNTING_OFF:
			if (me->_t)	{
				if (!--me->_t) {  					// decrementar t restante
					if (me->_onStartTon != null) 	// evitar null pointer
						me->_onStartTon(me->_id); 	// si llegó a 0, lanzar evento
									
					me->_t = me->_Ton;	
					me->_state = COUNTING_ON;						
				}
			}
			break;
	}		
}
//	

