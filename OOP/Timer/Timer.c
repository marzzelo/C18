//+--------------------------------------------------------------------------+
//|  $Workfile:: Timer.c                           $ $Revision:: 2           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 5/03/12 7:46a                                                $
//|  $Archive:: /@C18/SRC/Explorer1/Timer.c                                  $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "Timer.h"

DEFINE_THIS_FILE;
 
	Timer *Timer_ctor(Timer *me, 
					  void *parent,
					  uint16_t dt, 
					  uint16_t nTicks,
					  Handler onTimeElapsed,
					  Handler onTicksDone)
{
	ASSERT(dt > 0);
	me->_parent = parent;							// Guardar objeto contenedor
	me->_onTimeElapsed = onTimeElapsed;	
	me->_onTicksDone = onTicksDone;
	me->_dt = dt;
	me->_nTicks = nTicks;
	me->_t = 0;				// stopped;
	me->_nS = 1;
	me->_enabled = FALSE;
	return me;
} 

void Timer_start(Timer *me)
{
	me->_nS = me->_nTicks;
	me->_t = me->_dt;
	me->_enabled = TRUE;
}

void Timer_stop(Timer *me)
{
	me->_enabled = FALSE;
	me->_nS = 1;
	me->_t = 0;		
}

	
Timer *Timer_set_dt(Timer *me, uint16_t dt)
{
	ASSERT(dt > 0);
	me->_dt = dt;
	return me;
}


Timer *Timer_set_nTicks(Timer *me, uint16_t nTicks)
{
	me->_nTicks = nTicks;
	return me;
}


// Colocar en ISR de algún timer (ej.: 1ms)
void Timer_update(Timer *me)
{
	if (!me->_enabled)
		return;
		
	if (me->_t)	{
		if (!--me->_t) {				// decrementar t restante
			if (me->_onTimeElapsed != null) me->_onTimeElapsed(me->_parent); // si llegó a 0, llamar al EH()
			if (me->_nTicks > 0) {
				if (!me->_nS--) {
					me->_enabled = FALSE;
					if (me->_onTicksDone != null) me->_onTicksDone(me->_parent);
					return;
				}
			}	
			me->_t = me->_dt;		// continuar muestreando
		}
	}
}
	

