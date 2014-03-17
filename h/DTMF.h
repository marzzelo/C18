//;+------------------------------------------------------------------+
//;|       $Workfile:: DTMF.h                     $ $Revision:: 13    $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 19/06/09 9:45p                                 $
//;|        $Archive:: /@CODE/SRC/GSM4620/DTMF.h                      $
//;+------------------------------------------------------------------+

#ifndef _DTMF_H
#define _DTMF_H

#include "typedefs.h"
#include "cplus.h"
/*===============================================================================
 								VER EJEMPLO AL FINAL 
  ===============================================================================*/

/* Nombres para las teclas no numéricas */
#define KEY_ZERO 	0x0A  
#define KEY_ESCAPE 	0x0B /* Asterisco */
#define KEY_ENTER 	0x0C /* Numeral # */

#define ABC_DELAY		    4  /* 400 msec para fijar tecla en modo ABC */
#define DEFAULT_TIMEOUT		10 /* 10 segundos para cancelar entrada */



/* Estructura de bits del miembro ".control" de la estructura DTMFData */
typedef struct cntl8870 cntl8870;
struct cntl8870
{
	unsigned std:1;  /* Delayed Steering pin */
	unsigned hook:1; /* Hook Detector Output (on-hook = 1) */
	unsigned toe:1;  /* Tristate Output Enable (High: Chip ENABLED) */
	unsigned:4;
};

typedef cntl8870 (*OnControlBitsRequired_t)(void);		// DEFINICIÓN OBLIGATORIA

typedef BOOL (*OnKeyRead_t)(byte);						// DEFINICIÓN OPCIONAL

/* Una de las siguientes constantes debe ser especificada al
   llamar al método DTMFstore() para indicar el formato en que 
   el dato recibido se almacenará en el buffer */
typedef enum GetterType 
{
	BINARY, 
	DIGIT,	
	ABC
} GetterType;

/* Return Codes para el método DTMFstore */
typedef enum DTMFrc 
{
	DTMF_OK, 
	DTMF_TIMEOUT, 
	DTMF_HOOK, 
	DTMF_MAXLEN,
	DTMF_CANCEL			/* Usuario devuelve MSG_RETURN en OnKeyRead() */
} DTMFrc;


/*****************************************************
 *  			CLASS DTMFDriver					 *
 *****************************************************/
CLASS(DTMFDriver)
	/*--- Campos ---*/	
	char EOFchar;  			/* El caracter para EOF (0 al 9, * ó #) */
	int TimeOut;		   	/* Tiempo máximo de espera entre teclas */
	
	char *data__;		   	/* Acceso al puerto del 8870 */
	char *tris__;		   	/* Acceso al tris del puerto del 8870 */
	char mask__;		   	/* Mascara de nibble para el puerto del 8870 */
	int *TimeOutTimer1s__; 	/* Temporizador funcionando con tics de 1 segundo */
	int *AbcTimer100ms__;  	/* Temporizador funcionando con tics de 100 ms */
	
	/*--- Eventos ---*/
	OnControlBitsRequired_t OnControlBitsRequired__;
	OnKeyRead_t OnKeyRead;	
	
METHODS
	/* Constructor */
	DTMFDriver *DTMFDriverCtor_(DTMFDriver *me,
								char *datos, char* tris, char mask,
								OnControlBitsRequired_t OnControlBitsRequired,
								int *timeOutTimer1s, int *abcTimer100ms);

	/* Devuelve el caracter leído en formato binario */
	byte DTMFGetBin(DTMFDriver *me);					/* 0x01 ... 0x0C */
	
	/* Devuelve el caracter leído en formato ASCII Numérico */
	byte DTMFGetDigit(DTMFDriver *me);				/* '1','2'... '0','*','#' */
	
	/* Leer un caracter en modo ABC. Cada tecla puede pulsarse hasta 4 veces.
	 * La 4ª vez corresponde al número de la tecla.
	 * Una pausa de más de 400 ms supone que se ha elegido la letra
	 * La tecla cero escribe espacio, guiones y el cero. */
	byte DTMFGetABC(DTMFDriver *me);				/* 'a','b','c'...'z', '0','1'...'#' */

	/* Guardar una cadena terminada con la tecla 'DTMFEOFchar__' 
	 * El modo (GetMode) puede ser: BINARY, DIGIT o ABC
	 * Según el modo indicado se llamará a alguna de las tres funciones
	 * get() getDigit() o getABC() y el caracter resultante se almacenará 
	 * en el buffer hasta recibir EOFchar */	
	DTMFrc DTMFStore(DTMFDriver *me, GetterType GetMode, byte *buff, byte MaxLen);

END_CLASS

#endif
//
/******************************************************************************
 *                                   EJEMPLO                                  *
 ******************************************************************************
 
===============================================================================
INSTANCIACIÓN: 
===============================================================================
1) Declarar el objeto y definir un buffer de bytes:

					DTMFDriver		Tel;
					byte			TelBuff[25];

2) Definir un handler para pasar los bits leídos desde los pines de control
	del 8870. El handler debe devolver una estructura de tipo cntl8870 
	con el valor recogido de los tres bits de control, por ejemplo:
	
					cntl8870 Tel_OnControlBitsRequired(void)
					{
						cntl8870 DR;
						
						DR.std = StD;
						DR.hook = HOOK;
						DR.toe = TOE;
						return DR;
					}

3) Opcionalmente, Definir un handler para el evento OnKeyRead() que se lanza
	en el método DTMFstore(), por ejemplo:

					
					BOOL Tel_OnKeyRead(byte c)
					{
						if (c == '*')					
							return FALSE;
					
						return TRUE;						
					}

===============================================================================
INICIALIZACIÓN
===============================================================================
4) Llamar al constructor, pasandole el puerto y el tris donde se encuentra el 
	bus de datos del 8870, una máscara para los bits utilizados, el handler
	antes mencionado OnControl... y dos timers que deben actualizarse 
	externamente, Tm de	periodo 1 seg y Tm2 de periodo 100ms:
	
					DTMFDriverCtor_(&Tel, 
									(char*)&PORTD, (char*)&TRISD, 0x0F,
									Tel_OnControlBitsRequired, 
									Tm, Tm2);


5) Opcionalmente, asignar un handler para OnKeyRead():

					Tel.OnKeyRead = Tel_OnKeyRead;
					
6) Opcionalmente, asignar el TimeOut para cancelar si no se presiona una tecla:

					Tel.TimeOut = 5;    // en segundos					


===============================================================================
USO
=============================================================================== 
7) Antes de llamar alguna de los métodos, debe habilitarse el chip mediante el
	pin TOE. Si luego desea utilizarse el mismo bus para otra aplicación, 
	hay que inhabilitar el chip, poniendo sus salidas en alta impedancia:
	
					TOE = TRUE;			
 					k = DTMFStore(&Tel, DIGIT, TelBuff, sizeof(TelBuff));
					TOE = FALSE;								
					
8) Puede determinarse el resultado evaluando el código de retorno:

					switch (k)
					{
						case DTMF_OK: printf((frchar*)"\n%d: OK", k); break;
						case DTMF_MAXLEN: printf((frchar*)"\n%d: MAXLEN", k); break;
						case DTMF_TIMEOUT: printf((frchar*)"\n%d: TIMEOUT", k); break;
						case DTMF_HOOK: printf((frchar*)"\n%d: USER HOOK", k); break;
						case DTMF_CANCEL: printf((frchar*)"\n%d: USER CANCELLED", k); break;
					}
					
===============================================================================					
*/

