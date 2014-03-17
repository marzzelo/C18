//;+------------------------------------------------------------------+
//;|       $Workfile:: bitgetdw.c                 $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 17/12/09 6:09p                                 $
//;|        $Archive:: /@CODE/obj/bitops/bitgetdw.c                   $
//;+------------------------------------------------------------------+
#include "bitops.h"
#include "typedefs.h"
#include <stdio.h>

          

DWORD bitgetdw(const DWORD* intflag, char bt)
{
	DWORD result;
	result._dword = 0x00000000;
	
	
 	if (bt > 23)
		result.byte3 = intflag->byte3 & (1 << (bt - 24));

	else if (bt > 15)
		result.byte2 = intflag->byte2 & (1 << (bt - 16));

	else if (bt > 7)
		result.byte1 = intflag->byte1 & (1 << (bt - 8));

	else 
		result.byte0 = intflag->byte0 & (1 << bt);
	
	//printf((frchar*)"\nbit get: %d  %04b.%04b.%04b.%04b\n", bt, result.byte3, result.byte2, result.byte1, result.byte0);
	return result;
}//

