//+--------------------------------------------------------------------------+
//|  $Workfile:: qassert.c                           $ $Revision:: 2         $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 18/06/11 5:39p                                               $
//|  $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/qassert.c          $
//+--------------------------------------------------------------------------+


#include <stdio.h>		

void onAssert__(char const *file, unsigned line) 
{
	printf((rom far char*)"\r\nASSERTION ERROR: File %s, Line %d\r\n", file, line);
STALL:
	goto STALL;	
}
