//;+------------------------------------------------------------------+
//;|       $Workfile:: strcatf.c                  $ $Revision:: 8     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 25/12/09 6:08p                                 $
//;|        $Archive:: /@CODE/obj/xstrings/strcatf.c                  $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>
#include <stdio.h>

/*************************************************************************//**
 
 ****************************************************************************/
int strcatf(char *dest, const char *src, unsigned int sizeOfDest)
{
	int free = sizeOfDest - (strlen(dest) + strlen(src));
	
//	printf((far rom char*)"\r\ndest: %s\r\nsrc: %s\r\n", dest, src);
//	printf((far rom char*)"\r\n-> strcatf: %d = %d - (%d + %d)\r\n", 
//				free, 
//				sizeOfDest, 
//				strlen(dest), 
//				strlen(src));
				
	if (free >= 0)
		strcat(dest, src);

	return free;	
}
//
