//;+------------------------------------------------------------------+
//;|       $Workfile:: bitgetw.c                  $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 17/12/09 6:10p                                 $
//;|        $Archive:: /@CODE/obj/bitops/bitgetw.c                    $
//;+------------------------------------------------------------------+
#include "bitops.h"
#include "typedefs.h"
#include <stdio.h>

          

WORD bitgetw(const WORD* intflag, char bt)
{
	WORD result;
	result._word = 0x0000;
	
	
 	if (bt > 7)
		result.byte1 = intflag->byte1 & (1 << (bt - 8));
	
	else
		result.byte0 = intflag->byte0 & (1 << bt);
	
	return result;
}//

