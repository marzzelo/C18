//;+------------------------------------------------------------------+
//;|       $Workfile:: strcatfpgm2ram.c           $ $Revision:: 5     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 25/12/09 12:55p                                $
//;|        $Archive:: /@CODE/obj/xstrings/strcatfpgm2ram.c           $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>

/*************************************************************************//**
 
 ****************************************************************************/
int strcatfpgm2ram(char *dest, 
						   const far rom char *src, 
						   sizerom_t sizeOfDest)
{
	int free = (char)(sizeOfDest - (strlen(dest) + strlenpgm(src)));
	
	if (free >= 0)
		strcatpgm2ram(dest, src);

	return free;	
}
//
