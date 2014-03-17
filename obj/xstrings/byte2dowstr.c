//;+------------------------------------------------------------------+
//;|       $Workfile:: byte2dowstr.c              $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 13/12/11 9:51p                                 $
//;|        $Archive:: /@C18/obj/xstrings/byte2dowstr.c               $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include "xstrings.h"

static char rom far const *dows[] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB" };

#pragma code
/*****************************************************************//** 
@Descripcion 	entrega un string[3] con el día de la semana
				a partir de un entero entre [0=DOM .. 6=SAB]

@param[in]		wkday		número del día de la semana comenzando en 0(DOM)
@return			dayOfWeek	puntero a string[3] con el día de la semana

<hr>
******************************************************************* **/ 
far rom char* byte2dowstr(unsigned char dowbyte)
{
	return dows[dowbyte];
}//
