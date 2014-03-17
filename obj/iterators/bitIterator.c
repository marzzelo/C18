//+--------------------------------------------------------------------------+
//|  $Workfile:: bitIterator.c                           $ $Revision:: 1     $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 18/10/10 9:02p                                               $
//|  $Archive:: /@CODE/obj/iterators/bitIterator.c                           $
//+--------------------------------------------------------------------------+


#include "typedefs.h"
#include "Iterators.h"

void ForEachBit(uint8_t mask, BitIterator iterFunct, void *parms) 
{
	uint8_t k = mask;
	uint8_t i;
	
	for (i=0; i<8; i++)
	{
		if (k & 0x01)
		{
			iterFunct(i, parms);
		}
		k >>= 1;
	}
}

						
