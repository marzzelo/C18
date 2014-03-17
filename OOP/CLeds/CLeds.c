//+--------------------------------------------------------------------------+
//|  $Workfile:: CLeds.c                           $ $Revision:: 13          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 3/04/12 12:20p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/CLeds.c                                  $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "CLeds.h"

DEFINE_THIS_FILE;

static	void _onTimeElapsed(void* this);	   			///< Handler para Timer 
static	void _onTicksDone(void* this);				///< Handler para Timer 
	

CLeds *CLeds_ctor(CLeds *me,
			port_t *ledPort,
			uint16_t dt, 
			uint16_t nTicks, 
			LedSequence sequence,
			LedSequence onLedsDone)
{
	ASSERT(dt > 0);
	*(ledPort + 18) = 0b00000000;	// Assuming: TRISx = LATx + 9 = PORTx + 18
	me->_ledPort = ledPort;
	me->_sequence = sequence;
	me->_onLedsDone = onLedsDone;
	me->_index = 0;	
	
	Timer_ctor(	&me->_ledTimer, 
				(void*)me, 
				dt, 
				nTicks, 
				_onTimeElapsed, 
				_onTicksDone);
	
	return me;
} //


void CLeds_arrayModeSetup(CLeds *me, 
			uint8_t *array,
			uint8_t arraySize,
			EventHandler onArrayCycle) 
{
	me->_array = array;
	me->_arraySize = arraySize;
	me->_onArrayCycle = onArrayCycle;
}//

void CLeds_startSeq(CLeds *me){
	me->_isModeSeq = TRUE;
	Timer_start(&me->_ledTimer);
}//

void CLeds_startArray(CLeds *me){
	me->_isModeSeq = FALSE;
	Timer_start(&me->_ledTimer);
}//

void CLeds_pause(CLeds *me){
	me->_index = 0;
	Timer_stop(&me->_ledTimer);
}//


void CLeds_set(CLeds *me, uint8_t value) {
	CLeds_pause(me);
	me->_index = 0;
	*me->_ledPort = value;
}//

void CLeds_set_dt(CLeds *me, uint16_t dt) {
	Timer_set_dt(&me->_ledTimer, dt);
}//


void CLeds_set_nTicks(CLeds *me, uint16_t nTicks) {
	Timer_set_nTicks(&me->_ledTimer, nTicks);
}//


void CLeds_update(CLeds *me){
	Timer_update(&me->_ledTimer);
}//


void CLeds_newSequence(CLeds *me, LedSequence newSequence, uint16_t nTicks){
	Timer_set_nTicks(&me->_ledTimer, nTicks);
	me->_sequence = newSequence;
	CLeds_startSeq(me);
}//


// Secuencias Standard 
uint8_t ledSeqConstant(uint8_t value) {
	return value;
}//


static void _onTimeElapsed(void *this) {
	CLeds *me = (CLeds*)this;

	if (me->_isModeSeq) {
		*me->_ledPort = me->_sequence();
		return;
	}

	*me->_ledPort = me->_array[me->_index++]; 
	if (me->_index >= me->_arraySize) {
		me->_index = 0;
		me->_onArrayCycle();
	}
}

static void _onTicksDone(void *this){
	CLeds *me = (CLeds*)this;
	
	*me->_ledPort = me->_onLedsDone();
}//

