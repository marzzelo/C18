//;+------------------------------------------------------------------+
//;|       $Workfile:: strextract.c               $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 10/12/09 10:47p                                $
//;|        $Archive:: /@CODE/obj/xstrings/strextract.c               $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>


/*****************************************************************//** 
$Revision: 2 $  <hr>
@Descripcion 	Extrae un substring encapsulado con "" dentro
				de otro string.

@param[in]		str_dest	buffer de salida del string extraido
@param[in]		str_src		string donde se encuentra el encapsulado

<hr>
******************************************************************* **/ 
void strextract(char* str_dest, char* str_source)
{
	static const far rom char quotation[] = "\"";
	
	char* pos = strtokpgmram(str_source, quotation);
	if ((pos = strtokpgmram(NULL, quotation)) == NULL)
		str_dest[0] = '\0';
	else
		strcpy(str_dest, pos);
		
}//
	 
	 
