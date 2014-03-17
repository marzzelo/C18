//+--------------------------------------------------------------------------+
//|  $Workfile:: reader.c                              $ $Revision:: 6       $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 15/03/12 3:27p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/reader.c                                 $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include "typedefs.h"
#include "Reader.h"
#include "qassert.h"
#include "string.h"

DEFINE_THIS_FILE;

typedef enum ReaderStatesTag {
	IDLE,
	ESPERANDO,
	RECIBIENDO,
} ReaderStates;

#pragma udata RBUFF
char rBuff[250];
#pragma udata

CBuff  aCBuff;
Reader theReader;

static void vf(void) {
	Nop();

}//

/***************************************
 *                                     * 
 *            constructor              *
 *                                     *
 ***************************************/
void Reader_ctor(		Reader *me,
						CBuff *cBuff,  
						char *eolChars,
						uint8_t eolCharsSize,
						uint16_t timeOut,
						ReaderEventHandler onStringReceived)
{
	me->_cBuff = cBuff;
	me->_timeOut = timeOut;     			  // timeout permanece cte., tmr varía
	me->_tmr = 0;
	me->_eolChars = eolChars;
	me->_eolCharsSize = eolCharsSize;
	me->_onStringReceived = onStringReceived;
	me->_st = IDLE;
	me->_ready = FALSE;
} //


// Objeto ejemplo
void theReader_ctor(char *eolChars,
						uint8_t eolCharsSize,
						uint16_t timeOut,
						ReaderEventHandler onStringReceived) {
							
	// CONSTRUCCION DEL CBuff:							
	CBuff_ctor(	&aCBuff,
				rBuff, DIM(rBuff), 
				vf); 											// onBufferFull
				
	theReader._cBuff = &aCBuff;
	theReader._eolChars = eolChars;
	theReader._eolCharsSize = eolCharsSize;
	theReader._timeOut = timeOut;
	theReader._onStringReceived = onStringReceived;
	theReader._st = IDLE;
	theReader._ready = FALSE;
}
//


/*--------------------------------------------------------------------------*/
void Reader_start(Reader *me)
{
	me->_ready = FALSE;
	me->_tmr = 0;
	me->_st = ESPERANDO;
}

void Reader_stop(Reader *me)
{
	me->_ready = TRUE;
	me->_tmr = 0;
	me->_st = IDLE;
}
			
void Reader_read(Reader *me, char *outBuff) 
{
	uint8_t i = 0;
	
	while (OK == CBuff_pop(me->_cBuff, outBuff++));
}			
			
void Reader_clearBuff(Reader *me)
{
	CBuff_clear(me->_cBuff);
}

void Reader_update(Reader *me)
{
	if (me->_tmr) {
		if (!--me->_tmr) {
			if (me->_st != IDLE) {
				CBuff_push(me->_cBuff, '\0');
				me->_ready = TRUE;
				me->_st = IDLE;	
				if (me->_onStringReceived != null) 
					me->_onStringReceived(TIMEOUT);				
			}	
		} 
	}
}//
			

void Reader_push(Reader *me, char data)
{
	ReaderRc rc;

	switch (me->_st) {

		/*-------------------------*/
		case ESPERANDO: {
			if (memchr((void*)me->_eolChars, data, me->_eolCharsSize) != NULL)
				break;						    // descartar eol subsiguientes
				
			CBuff_push(me->_cBuff, data);
			me->_tmr = me->_timeOut;
			me->_st = RECIBIENDO;
			break;
		}	
			
		/*-------------------------*/
		case RECIBIENDO:
						
			// Buffer full?
			if (CBuff_getFree(me->_cBuff) == 1)	{
				CBuff_push(me->_cBuff, '\0');
				rc = BUFFER_FULL;						
				
				Reader_stop(me);
				if (me->_onStringReceived != null) 
					me->_onStringReceived(rc);
					
				break;
			}
			
			if (memchr((void*)me->_eolChars, data, me->_eolCharsSize) != NULL) {
				//CBuff_push(me->_cBuff, data);
				CBuff_push(me->_cBuff, '\0');
				rc = OK;
				
				if (me->_onStringReceived != null) 
					me->_onStringReceived(rc);
				
				me->_ready = FALSE;
				me->_tmr = 0;
				me->_st = ESPERANDO;
				break;
			}	

			
			// normal receiving...
			CBuff_push(me->_cBuff, data);
			me->_tmr = me->_timeOut;
			break; 
		
		/*-------------------------*/
		case IDLE:
			return;								 // stopped, esperando start()
	}
}//
