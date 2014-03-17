//+--------------------------------------------------------------------------+
//|  $Workfile:: CBuff.c                          $ $Revision:: 12        $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 15/03/12 3:23p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/CBuff.c                               $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h> 
#include "typedefs.h"
#include "CBuff.h"
#include "qassert.h"
#include "string.h"

DEFINE_THIS_FILE;


/***************************************
 *                                     * 
 *            constructor              *
 *                                     *
 ***************************************/
CBuff* CBuff_ctor(	CBuff *me, 
					char *buff,
 					uint8_t buffSize,
 					EventHandler onBufferFull)
{
	ASSERT(buffSize > 0);
	ASSERT(buffSize <= 254);  // 255 + 1 = 0 < 255 !!
	me->_buff = buff;
	me->_buffSize = buffSize;
	me->_bytesToRead = 0;
	me->_readPointer = 0;
	me->_writePointer = 0;
	memset(buff, 0x00, buffSize);
	me->_onBufferFull = onBufferFull;
	me->_dataSetReady = FALSE;
	return me;
} 


BuffStatus CBuff_push(CBuff *me, char c)
{
	if (me->_bytesToRead == me->_buffSize)	{
		if (me->_onBufferFull != null) me->_onBufferFull();
		return BUFF_FULL; 
	}
	
	me->_buff[me->_writePointer++] = c;
	if (me->_writePointer >= me->_buffSize) {
		me->_writePointer = 0;
	}
		
	++me->_bytesToRead;
	return OK;
}//


BuffStatus CBuff_pushString(CBuff *me, const char *str) {
	char *pos = str;
	BuffStatus RC = OK;
	
	while(BUFF_FULL != CBuff_push(me, *pos++)) {
		if (*pos == '\0') // end of string?
			return RC;
		ClrWdt();	
	}
	return RC;
}//

BuffStatus CBuff_pushRomString(CBuff *me, const far rom char *romStr) {
	char ramStr[64];
	
	strcpypgm2ram(ramStr, romStr);
	return CBuff_pushString(me, ramStr);
}//


BuffStatus CBuff_pop(CBuff const *me, char *c)
{
	if (me->_bytesToRead == 0)	{
		return BUFF_EMPTY; 
	}
	
	*c = me->_buff[me->_readPointer++];
	if (me->_readPointer >= me->_buffSize) {
		me->_readPointer = 0;
	}
	--me->_bytesToRead;
	return OK;
}//

BuffStatus CBuff_popString(CBuff const *me, char *strOut) {
	while (BUFF_EMPTY != CBuff_pop(me, strOut++)) {
		ClrWdt();
	}
	
	*strOut = '\0';
	return BUFF_EMPTY;
}//

void CBuff_clear(CBuff *me) 
{
	me->_bytesToRead = 0;
	me->_readPointer = 0;
	me->_writePointer = 0;
	memset(me->_buff, 0x00, me->_buffSize);
	me->_dataSetReady = FALSE;	
}//

void CBuff_set_Ready(CBuff *me, BOOL dataSetReady) 
{
	me->_dataSetReady = dataSetReady;
}

BOOL CBuff_isReady(CBuff *me) 
{
	return me->_dataSetReady;
}

uint8_t CBuff_getBytesToRead(CBuff *me)
{
	return me->_bytesToRead;
}

uint8_t CBuff_getFree(CBuff *me) 
{
	return (me->_buffSize - me->_bytesToRead);
}
//
