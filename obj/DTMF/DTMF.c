//;+------------------------------------------------------------------+
//;|       $Workfile:: DTMF.c                     $ $Revision:: 12    $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 19/06/09 9:58p                                 $
//;|        $Archive:: /@CODE/SRC/GSM4620/DTMF.c                      $
//;+------------------------------------------------------------------+

#include <typedefs.h>  								      /* DWORD */
#include <p18cxxx.h>
#include <string.h>
#include <stdio.h>
#include <xusart.h>
#include "DTMF.h"					

#define me_data (*me->data__)
#define me_tris (*me->tris__)
#define me_mask (me->mask__)

#define me_std (me->OnControlBitsRequired__()).std
#define me_hook (me->OnControlBitsRequired__()).hook
#define me_toe (me->OnControlBitsRequired__()).toe

/* Getter para una de las tres funciones que devuelven el dato leído */
typedef byte (*DTMFgetter)(DTMFDriver*);

/* Manejador de evento default para OnKeyRead() */
static BOOL DefaultOnKeyReadHandler(byte c) { return TRUE; } //

/* Rutina para habilitar el puerto */
void PortEnable8870(DTMFDriver *me)  { me_tris |= me_mask; } //

/* CONSTRUCTOR */
DTMFDriver *DTMFDriverCtor_(DTMFDriver *me,
							char *datos, char* tris, char mask,
							OnControlBitsRequired_t OnControlBitsRequired,
							int *timeOutTimer1s, int *abcTimer100ms) {
	me->data__ = datos;
	me->tris__ = tris;
	me->mask__ = mask;
	me->OnKeyRead = DefaultOnKeyReadHandler;
	me->OnControlBitsRequired__ = OnControlBitsRequired;
	me->EOFchar = KEY_ENTER; 				/* EOF por default = tecla '#' */
	me->TimeOutTimer1s__ = timeOutTimer1s; 	/* El usuario debe actualizar el timer */
	me->AbcTimer100ms__ = abcTimer100ms; 	/* El usuario debe actualizar el timer */
	me->TimeOut = DEFAULT_TIMEOUT;
	return me;
}//

byte DTMFGetBin(DTMFDriver *me)
{
	byte HexDigit = me_data &= me_mask;		/* Leer dato desde el puerto */
	/*************/
	
	PortEnable8870(me);						/* Tomar bus */
	while (me_std && !me_hook)				/* Esperar key release */
		ClrWdt();
	
	return HexDigit;
}//

byte DTMFGetDigit(DTMFDriver *me)
{
	char tabla[] = "-1234567890*#";
	char c = DTMFGetBin(me);
	/**************/
	
	return (c == me->EOFchar)? c : tabla[c];
}//

/* Leer un caracter en modo ABC. Cada tecla puede pulsarse hasta 4 veces.
 * La 4ª vez corresponde al número de la tecla.
 * Una pausa de más de 400 ms supone que se ha elegido la letra
 * La tecla cero escribe espacio, guiones y el cero. */
byte DTMFGetABC(DTMFDriver *me)
{
	char tabla[] = "----qñz1abc2def3ghi4jkl5mno6prs7tuv8wxy9 -_0*.,:####";
	char abc_pos = 0;
	byte c = DTMFGetBin(me);
	/***************/
	
	*me->AbcTimer100ms__ = ABC_DELAY; 			/* Fijo en 400 ms */
	while (*me->AbcTimer100ms__) 
	{
		if (me_std) 
		{
			while (me_std) 						/* Esperar que se suelte la tecla */
				ClrWdt();
				
			++abc_pos;
			*me->AbcTimer100ms__ = ABC_DELAY; 	/* Reiniciar cuenta */
		} 
	} 
	return (c == me->EOFchar) ? c : tabla[c*4 + abc_pos];	/* el EOF no se traduce */
}//


/* Guardar una cadena terminada con la tecla 'DTMFEOFchar__' 
 * El modo (GetMode) puede ser BINARY, DIGIT o ABC.
 * Según el modo indicado se llamará a alguna de las tres funciones
 * get() getDigit() o getABC() y el caracter resultante se almacenará
 * en el buffer */
DTMFrc DTMFStore(DTMFDriver *me, GetterType GetMode, byte *buff, byte MaxLen)
{
	char i = 0;	byte c; 
	DTMFrc RC;
	DTMFgetter Getter = &DTMFGetBin;  							/* Preseleccionar modo BINARY */
	/***************/	
	
	PortEnable8870(me);											/* Tomar bus */

	/* Seleccionar la función a llamar */
	if(GetMode == DIGIT)		Getter = &DTMFGetDigit;
	else if(GetMode == ABC)		Getter = &DTMFGetABC;
	
	RC = DTMF_OK;
	
	do
	{
		*me->TimeOutTimer1s__ = me->TimeOut;
		do 														/* Esperar a que se presione alguna tecla */
		{
			ClrWdt();
			if (!*me->TimeOutTimer1s__) RC = DTMF_TIMEOUT;	/* Demasiada demora entre teclas */
			else if (me_hook)			RC = DTMF_HOOK;		/* Cuelga antes de ingresar EOL */		
		} while ((!me_std) && (RC == DTMF_OK));
			
		if (RC != DTMF_OK)	break;
		
		/* LEER TECLA *************************/
		c = (Getter)(me);
		if (!me->OnKeyRead(c))
			return DTMF_CANCEL;
		/**************************************/
	
		buff[i++] = c;
		if (i >= MaxLen) 				   				/* Máxima long especificada por el usuario */
			RC = DTMF_MAXLEN;
				
	} while ((c != me->EOFchar) && (RC == DTMF_OK)); /* Caracter de EOF recibido */
	  	   
	if (RC == DTMF_OK) --i; 					/* Reemplazar el caracter de finalización por 0x00 */
	buff[i] = 0x00;  						/* Terminar el string */
	return RC; 
}//


 
/*********************************************************************
 *             E S Q U E M A T I C O                                 *
 *********************************************************************/
 
 
