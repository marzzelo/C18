//;+------------------------------------------------------------------+
//;|       $Workfile:: list2byte.c                $ $Revision:: 3     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 10/03/10 9:01a                                 $
//;|        $Archive:: /@CODE/obj/xstrings/list2byte.c                $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>


/*************************************************************************//** 
 * @Descripcion	Convierte una lista de números en ASCII (ej: 12367) en un 
 *				byte con sus bits correspondientes seteados a 1
 * @param[in]	list	string conteniendo los números en ASCII (0-9)
 * @param[in]	base	número que corresponde al bit 0 (gral~ 0 ó 1)
 * @param[in]	maxDigit	máximo valor permitido en la cadena (entre 0 y 9)	
 * @test
 * @code        byte myByte = list2byte(myList, 1, 7);
 				                                                      @endcode
 ****************************************************************************/
unsigned char list2byte(const char* list, unsigned char base, unsigned char maxDigit)
{
	unsigned char i=0, nItem, bmask=0;
	
	
	while (nItem = list[i])											// != 0x00
	{
		nItem -= (0x30 + base);						    // convierte a escalar
		if (nItem < maxDigit) 
			bmask |= (1 << nItem);
		++i;
	}
	
	return bmask;
}//		


