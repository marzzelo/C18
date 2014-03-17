//+--------------------------------------------------------------------------+
//|  $Workfile:: UartWriter.c                          $ $Revision:: 13      $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 14/03/12 1:03p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/UartWriter.c                             $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include <stdio.h>
#include "typedefs.h"
#include "UartWriter.h"
#include "qassert.h"
#include "string.h"
#include "xusart.h"

DEFINE_THIS_FILE;

	
void UartWriter_ctor(UartWriter *me, CBuff const *cbuff, EventHandler onBufferEmpty) {
	me->_cbuff = cbuff;
	me->_onBufferEmpty = onBufferEmpty;
	me->_ready2print = FALSE;
}

void UartWriter_set_cBuff(UartWriter *me, CBuff const *cbuff) {
	me->_cbuff = cbuff;
}

void UartWriter_start(UartWriter *me) {
	me->_ready2print = TRUE;
}

void UartWriter_stop(UartWriter *me) {
	me->_ready2print = FALSE;
}

void UartWriter_update(UartWriter *me) {					 
	char txByte;

	if (me->_ready2print = TRUE) {
		while (CBuff_pop(me->_cbuff, &txByte) != BUFF_EMPTY) {
			putcharUART(txByte);
			//ClrWdt();
		}
		if(me->_onBufferEmpty != null) me->_onBufferEmpty();
	}	
}  	


/***************************************
 *                                     * 
 *           S I N G L E T O N         *
 *                                     *
 ***************************************/
UartWriter theUartWriter;


//
