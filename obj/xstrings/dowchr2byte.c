//;+------------------------------------------------------------------+
//;|       $Workfile:: dowchr2byte.c              $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 11/12/09 6:28p                                 $
//;|        $Archive:: /@CODE/obj/xstrings/dowchr2byte.c              $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>

static char dows[] = {"DLMIJVS"};

#pragma code

/*****************************************************************//** 
@Descripcion 	entrega un entero con el día de la semana [0..6]
				a partir de un char "D..S"  

@param[in]		*dow		día de la semana 
@return			dow2chr		entero correspondiente [0..6]
<hr>
******************************************************************* **/ 
unsigned char dowchr2byte(char dowchr)
{
	return chrPos(dows, dowchr);
}//
