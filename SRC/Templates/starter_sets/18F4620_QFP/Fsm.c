//+--------------------------------------------------------------------------+
//|  $Workfile:: Fsm.c                               $ $Revision:: 3         $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 18/06/11 8:57p                                               $
//|  $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/Fsm.c              $
//+--------------------------------------------------------------------------+


#include "typedefs.h"
#include "fsm.h"
#include "qassert.h"

DEFINE_THIS_FILE;


Fsm* Fsm_ctor(Fsm *me, uint8_t nStates, uint16_t t0[], const EventHandler eh[])
{
	uint8_t i;
	
	ASSERT(nStates <= 5);  					   // 255 se utiliza para STOP
	
	me->nStates = nStates;
	
	for (i = 0; i < nStates; i++)
	{
		me->eh[i] = eh[i];					// event handlers para cada estado
		me->t0[i] = t0[i];							// delays para cada estado
	}
	
	me->st = 255;												    // stopped
	return me;
} 

void Fsm_start(Fsm *me, uint16_t rep) 
{
	ASSERT(rep >= 1);
	
	me->t = me->t0[0];						  // iniciar primera temporización
	me->rep = rep;
	me->st = 0;					
}

void Fsm_stop(Fsm *me)
{
	me->st = 255;							  						// STOPPED
}


// Colocar en ISR de algún timer
void Fsm_update(Fsm *me)
{
	if (me->st == 255)
		return;														// STOPPED
		
	if (!--me->t)
	{
		me->eh[me->st]();
		me->t = me->t0[me->st + 1];
		if (++me->st == me->nStates)			  // Pasar al siguiente estado
		{										// Ultimo estado, parar o loop
			me->st = 255;									  		  // parar
			if (--me->rep)
			{
				me->t = me->t0[0];									   // loop
				me->st = 0;
			}
		}
	}
}
	

