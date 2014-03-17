//+--------------------------------------------------------------------------+
//|  $Workfile:: UartReader.c                          $ $Revision:: 11      $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/12/11 9:37a                                               $
//|  $Archive:: /@C18/SRC/MTS/UartReader.c                                   $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include "typedefs.h"
#include "UartReader.h"
#include "qassert.h"
#include "string.h"

DEFINE_THIS_FILE;

typedef enum ReaderStatesTag {
	IDLE,
	ESPERANDO,
	RECIBIENDO,
} ReaderStates;

/***************************************
 *                                     * 
 *            constructor              *
 *                                     *
 ***************************************/
void UartReader_ctor(	UartReader *me,
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
} 


/*--------------------------------------------------------------------------*/
void UartReader_start(UartReader *me)
{
	me->_ready = FALSE;
	me->_tmr = 0;
	me->_st = ESPERANDO;
}

void UartReader_stop(UartReader *me)
{
	me->_ready = TRUE;
	me->_tmr = 0;
	me->_st = IDLE;
}
			
void UartReader_clearBuff(UartReader *me)
{
	CBuff_clear(me->_cBuff);
}

void UartReader_update(UartReader *me)
{
	if (me->_tmr) {
		if (!--me->_tmr) {
			if (me->_st != IDLE) {
				CBuff_push(me->_cBuff, '\0');
				me->_ready = TRUE;
				me->_st = IDLE;	
				me->_onStringReceived(TIMEOUT);				
			}	
		} 
	}
}
			

void UartReader_push(UartReader *me, char data)
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
				
				UartReader_stop(me);
				me->_onStringReceived(rc);
				break;
			}
			
			if (memchr((void*)me->_eolChars, data, me->_eolCharsSize) != NULL) {
				CBuff_push(me->_cBuff, data);
				CBuff_push(me->_cBuff, '\0');
				rc = OK;
				
				UartReader_stop(me);
				me->_onStringReceived(rc);
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
}

/***************************************
 *                                     * 
 *         S I N G L E T O N           *
 *                                     *
 ***************************************/

UartReader theUartReader;

//	

