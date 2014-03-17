//;+------------------------------------------------------------------+
//;|       $Workfile:: Driver7446.h               $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 18/06/09 2:31p                                 $
//;|        $Archive:: /@CODE/SRC/GSM4620/Driver7446.h                $
//;+------------------------------------------------------------------+
#ifndef _DRIVER7446_H
#define _DRIVER7446_H

#include "typedefs.h"
#include "cplus.h"


							/* VER EJEMPLO AL FINAL */

#define KEY_c		0x0A
#define KEY_ci		0x0B	/* c invertida */
#define KEY_u		0X0C 
#define KEY_c_		0X0D	/* c subrayada */
#define KEY_t		0X0E


typedef BOOL (*OnCharOutput_t)(char p);


/*****************************************************
 *  			CLASS Driver7446					 *
 *****************************************************/
CLASS(Driver7446)
	/* Fields */
	int *Tmr100ms__;
	char *data__;		   /* Acceso al puerto del 7446 */
	char *tris__;		   /* Acceso al tris del puerto del 7446 */
	char mask__;		   /* Mascara de nibble para el puerto del 7446 */
	
	/* Events */
	OnCharOutput_t OnCharOutput;	
	
METHODS
	/* Constructor */
	Driver7446 *Driver7446Ctor_(Driver7446 *me, 
								char *datos, char *tris, char mask,
								int *Tmr100ms);
	
	void OutDigit(Driver7446 *me, char dig);
	void OutBinary(Driver7446 *me, byte bin);
	void OutString(Driver7446 *me, char* str, int Ton, int Toff);
END_CLASS	


#endif 
//


