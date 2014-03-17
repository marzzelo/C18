//;+------------------------------------------------------------------+
//;|       $Workfile:: strLocate.c                $ $Revision:: 5     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 13/12/11 3:18p                                 $
//;|        $Archive:: /@C18/SRC/MTS/strLocate.c                      $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>

/*************************************************************************//**
 Ubica un string dentro de una tabla, devolviendo su posición
 En caso de no encontrar coincidencia, retorna table_size
 
 @param[in] str1        string a localizar
 @param[in] table	    Puntero a ROM donde con todos los textos de los URC
 @param[in] compLen		Cantidad de caracteres a comparar. 0 -> hasta strlen(str1)
 @param[in] table_size	cantidad de palabras listadas en table
 @return    uchar	    ubicación dentro de la tabla
 ****************************************************************************/
unsigned char strLocate(const char *str1, 
						far rom const char *table[],
						unsigned char compLen, 
						unsigned char table_size)
{
    unsigned char i;
    unsigned char len = compLen;
    
    for (i = 0; i < table_size; i++) 
	{
		if (compLen == 0)
    		len = strlenpgm(table[i]);
    		
	    if (!memcmppgm2ram((void*)str1,
	    				   (far rom void*)table[i], 
	    				    len))
            break;
    }
    return i;                    /* retorna table_size si no es URC */
}//


/*************************************************************************//**
 Ejemplo:
 
 typedef enum StatusTypeTag {
	REC_READ, 		0
	REC_UNREAD,		1
	STO_SENT,		2
	STO_UNSENT,		3
	STATUS__MAX		4
} StatusType;


static char rom far const *statusTable[] = {
	"READ", "UNREAD", "SENT", "UNSENT"
};//

void main()	
{
	char stat[] = "UNREAD";
	StatusType st;

	st = (StatusType)strLocate(stat, statusTable, STATUS__MAX); // returns -> 1
	switch (st)
	{
		case REC_READ:
			...
			break;
		case REC_UNREAD:
			...
			break;
			...
		...
	}
}



 ****************************************************************************/
