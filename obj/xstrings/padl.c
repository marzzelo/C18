//;+------------------------------------------------------------------+
//;|       $Workfile:: padl.c                     $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 10/12/09 10:41p                                $
//;|        $Archive:: /@CODE/obj/xstrings/padl.c                     $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>


void padl(char* str_topad, char padchar, unsigned char numchars)
{
	char i;
	
	
	for (i = strlen(str_topad); i >= 0; i--)
		str_topad[i+numchars] = str_topad[i];

	for (i = 0; i < numchars; i++)
		str_topad[i] = padchar;
		
}//		


