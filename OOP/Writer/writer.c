//+--------------------------------------------------------------------------+
//|  $Workfile:: writer.c                          $ $Revision:: 4           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 14/03/12 9:52a                                               $
//|  $Archive:: /@C18/SRC/Explorer1/writer.c                                 $
//+--------------------------------------------------------------------------+

#include "qassert.h"
#include "writer.h"
#include "xusart.h"
#include "string.h"

DEFINE_THIS_FILE;

Writer theWriter;
#pragma udata WBUFF
char theBuff[255];
#pragma udata

#pragma code
Writer *Writer_ctor(Writer *me, char *wbuff)
{
	me->_wbuff = wbuff;
	me->_enabled = TRUE;
	return me;
} 

void Writer_start(Writer *me) {
	me->_enabled = TRUE;
}

void Writer_stop(Writer *me) {
	me->_enabled = FALSE;
}

void Writer_update(Writer *me) {
	if (!me->_enabled) return;
	
	if (me->_wbuff[0]) {
		xputsUART(me->_wbuff);
		me->_wbuff[0] = 0x00;
	}
}

void Writer_putString(Writer *me, char *str) {
	strcpy(me->_wbuff, str);
}

void Writer_putrString(Writer *me, frchar* str) {
	strcpypgm2ram(me->_wbuff, str);
}
//

