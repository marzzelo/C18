//+--------------------------------------------------------------------------+
//|  $Workfile:: TBase.c                           $ $Revision:: 17          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 23/02/12 12:24p                                              $
//|  $Archive:: /@C18/SRC/Explorer1/TBase.c                                  $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "TBase.h"

DEFINE_THIS_FILE;
 
TBase *TBase_ctor(TBase *me, 
				  uint16_t dt, 
				  uint16_t nTicks,
				  EventHandler onTimeElapsed,
				  EventHandler onTicksDone)
{
	ASSERT(dt > 0);
	
	me->_onTimeElapsed = onTimeElapsed;	
	me->_onTicksDone = onTicksDone;
	me->_dt = dt;
	me->_nTicks = nTicks;
	me->_t = 0;				// stopped;
	me->_nS = 1;
	me->_enabled = FALSE;
	return me;
} 

void TBase_start(TBase *me)
{
	me->_nS = me->_nTicks;
	me->_t = me->_dt;
	me->_enabled = TRUE;
}

void TBase_stop(TBase *me)
{
	me->_enabled = FALSE;
	me->_nS = 1;
	me->_t = 0;		
}

	
TBase *TBase_set_dt(TBase *me, uint16_t dt)
{
	ASSERT(dt > 0);
	me->_dt = dt;
	return me;
}


TBase *TBase_set_nTicks(TBase *me, uint16_t nTicks)
{
	me->_nTicks = nTicks;
	return me;
}


// Colocar en ISR de algún timer (ej.: 1ms)
void TBase_update(TBase *me)
{
	if (!me->_enabled)
		return;
		
	if (me->_t)	{
		if (!--me->_t) {				// decrementar t restante
			if (me->_onTimeElapsed != null) me->_onTimeElapsed(); // si llegó a 0, llamar al EH()
			if (me->_nTicks > 0) {
				if (!me->_nS--) {
					me->_enabled = FALSE;
					if (me->_onTicksDone != null) me->_onTicksDone();
					return;
				}
			}	
			me->_t = me->_dt;		// continuar muestreando
		}
	}
}
	

