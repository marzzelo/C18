//+--------------------------------------------------------------------------+
//|  $Workfile:: Relay.c                           $ $Revision:: 3           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/09/13 9:15                                                $
//|  $Archive:: /@C18/SRC/LATCH2/Relay.c                                     $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "Relay.h"
#include <stdio.h>

DEFINE_THIS_FILE;

Relay *Relay_ctor(Relay *me, 
				  uint8_t id,
				  uint16_t Ton, 
				  uint16_t Toff,
				  uint16_t cycles,
				  RelayHandler onStartTon,
				  RelayHandler onStartToff,
				  RelayHandler onCyclesCompleted,
				  BOOL startHI)
{
	ASSERT(me->_Ton > 0); 	/* ERROR: Ton no puede ser 0 o negativo */
	ASSERT(me->_Toff > 0);	/* ERROR: Toff no puede ser 0 o negativo */
	me->_id = id;
	me->_Ton = Ton;
	me->_Toff = Toff;
	me->_cycles = cycles;
	me->_t = 0;				// stopped;
	me->_c = 0;
	me->_enabled = FALSE;

	me->_onStartTon = onStartTon;	
	me->_onStartToff = onStartToff;
	me->_onCyclesCompleted = onCyclesCompleted;
	me->_startHI = startHI;
	me->_state = IDLE;
	return me;
} 

void Relay_start(Relay *me)
{
	ASSERT(me->_Ton > 0); 	/* ERROR: se ha instanciado el objeto? */
	ASSERT(me->_Toff > 0);	/* ERROR: se ha instanciado el objeto? */
	me->_c = me->_cycles;
	if (me->_startHI) {
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
	me->_enabled = TRUE;
}//

void Relay_stop(Relay *me)
{
	me->_t = 0;
	me->_state = IDLE;
}//


void Relay_pause(Relay *me)
{
	me->_enabled = FALSE;
}//

void Relay_resume(Relay *me)
{
	me->_enabled = TRUE;
}//

// Colocar en ISR de algún timer (ej.: 1ms)
void Relay_update(Relay *me)
{
	ASSERT(me->_Ton > 0); 	/* ERROR: se ha instanciado el objeto? */
	ASSERT(me->_Toff > 0);	/* ERROR: se ha instanciado el objeto? */
	
	if (!me->_enabled)
		return;
		
	switch (me->_state) {
		case IDLE:
			break;
			
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

