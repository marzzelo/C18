//;+------------------------------------------------------------------+
//;|       $Workfile:: ftos.c                     $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 18/12/13 9:33                                  $
//;|        $Archive:: /@C18/SRC/ADAQUS/ftos.c                        $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>
/*************************************************************************//** 
Convierte un float a string para poder imprimirlo con printf.
@param[in]	fd    	Float a convertir toString
@param[out] s		puntero al string de salida
@param[in]  multiplier  indicador de decimales deseados (100: 2 decimales,
			1000: 3 decimales o 10000: 4 decimales)
*****************************************************************************/
void ftos(float fd, char s[], unsigned int multiplier) {
	// multiplier = 10, 100, 1000 or 10000
	long lWhole = (long)((float)fd);
	unsigned long ulPart = (long)((float)fd*multiplier)-lWhole*multiplier;
	sprintf(s, (far rom char *)"%li.%li", lWhole, ulPart);
}	//


