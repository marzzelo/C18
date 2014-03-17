//;+------------------------------------------------------------------+
//;|       $Workfile:: countbitsU32.c             $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 15/12/11 1:39p                                 $
//;|        $Archive:: /@C18/obj/bitops/countbitsU32.c                $
//;+------------------------------------------------------------------+

#include "typedefs.h"

uint8_t countbitsU32(uint32_t b)
{
	unsigned char count;
	
	for (count = 0; b != 0; count++)
	{
		b &= b - 1; // this clears the LSB-most set bit
	}
	
	return (count);
}
