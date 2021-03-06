//;+------------------------------------------------------------------+
//;|       $Workfile:: bitsetdw.c                 $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 17/12/09 6:06p                                 $
//;|        $Archive:: /@CODE/obj/bitops/bitsetdw.c                   $
//;+------------------------------------------------------------------+
#include "bitops.h"
#include "typedefs.h"
#include <stdio.h>


DWORD bitsetdw(DWORD* dwflag, char bt)
{
 	if (bt > 23)
		dwflag->byte3 |= (1 << (bt - 24));

	else if (bt > 15)
		dwflag->byte2 |= (1 << (bt - 16));

	else if (bt > 7)
		dwflag->byte1 |= (1 << (bt - 8));

	else 
		dwflag->byte0 |= (1 << bt);
	
	//printf((frchar*)"\nbitset: %d  %04b.%04b.%04b.%04b\n", bt, dwflag->byte3, dwflag->byte2, dwflag->byte1, dwflag->byte0);
	return *dwflag;
}//
