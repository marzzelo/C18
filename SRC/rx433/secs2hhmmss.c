//;+------------------------------------------------------------------+
//;|       $Workfile:: secs2hhmmss.c              $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 12/06/11 8:19p                                 $
//;|        $Archive:: /@CODE/obj/xstrings/secs2hhmmss.c              $
//;+------------------------------------------------------------------+


#include <stdio.h>
#include <xstrings.h>

void secs2hhmmss(char* hhmmss, unsigned int secs)
{
	char hh[] = "00";
	char mm[] = "00";
	char ss[] = "00";
	
	unsigned int  h, m, s;
	
	// secs = 12345
	
	h = secs/3600;
	m = (secs % 3600) / 60;
	s = secs % 60;
	
	//printf((frchar*)"\r\nDEBUG: %d --> %02d:%02d:%02d\r\n", secs, h, m, s);
	sprintf(hhmmss, (far rom char*)"%02d:%02d:%02d", h, m, s);
}//



