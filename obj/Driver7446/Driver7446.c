//;+------------------------------------------------------------------+
//;|       $Workfile:: Driver7446.c               $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 16/06/09 10:41p                                $
//;|        $Archive:: /@CODE/SRC/GSM4620/Driver7446.c                $
//;+------------------------------------------------------------------+

#include <typedefs.h>  								      /* DWORD */
#include <p18cxxx.h>
#include <string.h>
#include <stdio.h>
#include <driver7446.h>


#define me_data (*(me->data__))
#define me_tris (*(me->tris__))
#define me_mask (me->mask__)


static BOOL DummyFunction(char dummy){return TRUE;}//


/* Constructor */
Driver7446 *Driver7446Ctor_(Driver7446 *me, 
							char *datos, char *tris, char mask,
							int *Tmr100ms)
{					
	me->Tmr100ms__ = Tmr100ms;
	me->data__ = datos;
	me->tris__ = tris;
	me->mask__ = mask;
	me->OnCharOutput = DummyFunction;
}//

/* Properties */
		 							
	/* Methods */
void PortEnable7446(Driver7446 *me)
{
	me_tris &= ~me_mask;
}

void OutDigit(Driver7446 *me, char dig) 
{
	PortEnable7446(me);
	me_data |= (dig & me_mask);
	me_data &= (dig | ~me_mask);
}

void OutBinary(Driver7446 *me, byte bin)
{
	OutDigit(me, bin + '0');
}

void OutString(Driver7446 *me, char* str, int Ton, int Toff)
{
	char i = 0; 
	char p, p1;
	/***************/
	

	*me->Tmr100ms__ = Ton; /* Primera pausa algo superior */
	while(p = str[i++])
	{
		OutBinary(me, 0xFF);
			
		while (*me->Tmr100ms__) 
			ClrWdt();
		
		/* Corregir limitación para digito 0 del 8870 */
		OutBinary(me, (p1 = (p == 0x0A)? 0 : p));
		if(!(me->OnCharOutput(p1))) /* Evento (aquí se puede cancelar desde afuera)*/			
			return;

		
		*me->Tmr100ms__ = Ton;
		while (*me->Tmr100ms__) 
			ClrWdt();
			
		*me->Tmr100ms__ = Toff;
	}
}//


				
