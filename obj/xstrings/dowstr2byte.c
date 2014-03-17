//;+------------------------------------------------------------------+
//;|       $Workfile:: dowstr2byte.c              $ $Revision:: 3     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 11/12/09 6:22p                                 $
//;|        $Archive:: /@CODE/obj/xstrings/dowstr2byte.c              $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>

static char dows[] = {"DLMMJVSAI"};

#pragma code

/*****************************************************************//** 
@Descripcion 	entrega un entero con el día de la semana [0..6]
				a partir de un string "DOM...VIE"  

@param[in]		*dow		día de la semana 
@return			dow2chr		entero correspondiente [0..6]
<hr>
******************************************************************* **/ 
unsigned char dowstr2byte(const char *dowstr)
{
	char *dds = strchr(dows, dowstr[0]);
	char ddn = dds - dows;
	
	if (ddn == 2)				   // si es M, verificar segunda letra (A o I)
	{
		dds = strchr(dows, dowstr[1]);
		ddn = dds - dows - 5;
	}	
		
	return ddn;
}//
