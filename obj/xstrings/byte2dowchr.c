//;+------------------------------------------------------------------+
//;|       $Workfile:: byte2dowchr.c              $ $Revision:: 4     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 13/12/11 9:51p                                 $
//;|        $Archive:: /@C18/obj/xstrings/byte2dowchr.c               $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include "xstrings.h"

char dows[] = "DLMIJVS";

#pragma code
/*****************************************************************//** 
@Descripcion 	entrega un string[3] con el día de la semana
				a partir de un entero entre [0=DOM .. 6=SAB]

@param[in]		wkday		número del día de la semana comenzando en 0(DOM)
@return			dayOfWeek	puntero a string[3] con el día de la semana

<hr>
******************************************************************* **/ 
char byte2dowchr(unsigned char dowbyte)
{
	return dows[dowbyte];
}//
