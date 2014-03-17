//+--------------------------------------------------------------------------+
//|  $Workfile:: qassert.c                           $ $Revision:: 1         $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 19/11/11 2:27p                                               $
//|  $Archive:: /@C18/SRC/Templates/starter_sets/18F4620_OOP/qassert.c       $
//+--------------------------------------------------------------------------+


#include <stdio.h>		

void onAssert__(char const *file, unsigned line) 
{
	printf((rom far char*)"\r\nASSERTION ERROR: File %s, Line %d\r\n", file, line);
STALL:
	goto STALL;	
}
