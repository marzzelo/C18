//;+------------------------------------------------------------------+
//;|       $Workfile:: split.c                    $ $Revision:: 4     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 5/01/10 5:19p                                  $
//;|        $Archive:: /@CODE/obj/xstrings/split.c                    $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>
/*************************************************************************//** 
Separa las palabras de una línea, segun los delimitadores "delims".
@param[in]	line    Puntero al buffer donde se encuentra la línea 
@param[out]	parms   Puntero a un set de punteros a char
@param[in]  nWords	CAntidad máxima de palabras de la línea line
@param[in]  delims  delimitadores para strtok
*****************************************************************************/
void split(char *line,     
           char *parms[], 
           unsigned char nWords,
           const far rom char *delims) 
{
    unsigned char i;
    
    memset(parms, 0x00, 2*nWords);  // Preset. Cada puntero ocupa 2 bytes
    parms[0] = strtokpgmram(line, delims); 
	for (i = 1; i < nWords; i++) 
	{
    	parms[i] = strtokpgmram(NULL, delims);
    }
}//


