//+--------------------------------------------------------------------------+
//|  $Workfile:: CBuff.h                          $ $Revision:: 16           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 21/08/13 13:20                                               $
//|  $Archive:: /@C18/OOP/CBuff/CBuff.h                                      $
//+--------------------------------------------------------------------------+
//! \file CBuff.h
//! ### Buffer Circular de propósito general.


#ifndef CBUFF_H_
#define CBUFF_H_

#include "typedefs.h"

/** Códigos de retorno para CBuff_Push() y CBuff_Pop() */
typedef enum {
	OK,				///< Lectura o escritura normal del buffer
	BUFF_FULL,		///< Buffer Full al intentar escribir el primer caracter
	BUFF_EMPTY		///< Buffer Vacío al intentar leer el primer caracter
} BuffStatus;

/*************************************************************************//** 
 *  ##Buffer Circular de propósito general.
 * + Todos los campos deben considerarse PRIVATE. Sólo deben accederse 
 *	 mediante el constructor y metodos accesors. 
 * + Solamente el objeto contenedor puede escribir (Push) en el CBuff.
 * + El contenedor puede generar un evento **ofreciendo** la lectura del buffer,
 *     cuando los datos estén listos, a otro objeto **lector**, que debe **copiar**
 *     los datos en su propio buffer. 
 ****************************************************************************/
CLASS(CBuff)	
	BOOL _dataSetReady;		///< Datos listos para leer?
	char *_buff;			///< Buffer interno, hasta 256 bytes
	uint8_t _buffSize; 		///< DIM(_cbuff)
	uint8_t _bytesToRead;	///< Cantidad de datos no leidos en el buffer
	uint8_t _readPointer;	///< Index of last read char
	uint8_t _writePointer;	///< Index of last written char	
	EventHandler _onBufferFull;
METHODS

/*************************************************************************//** 
 * Constructor del Buffer Circular.
 *
 * @param[in]    me				This
 * @param[in]    cBuff			Buffer externo para el buffer circular
 * @param[in]    buffSize	    Tamaño del buffer asignado, usar DIM(cBuff)
 * @param[in]    onBufferFull   Controlador de evento BUFFER FULL 
 *
 * @returns      CBuff			puntero a This
 * @code Ejemplo:
 * 		CBuff_ctor(&cDaqBuff, daqBuff, DIM(daqBuff), NULL);
 * @endcode
 * @related	    CBuff
 ****************************************************************************/
CBuff* CBuff_ctor(	CBuff *me, 
					char *buff,
 					uint8_t buffSize,
 					EventHandler onBufferFull);

/*************************************************************************//** 
 * Inserta un byte en Buffer Circular.
 *
 * @param[in]    me				This
 * @param[in]    c				caracter a insertar (by value)
 *
 * @returns      BuffStatus		Estado del buffer
 * @code Ejemplo:
 * 		CBuff_push(&cDaqBuff, ++j);
 * @endcode
 * @related	    CBuff 
 ****************************************************************************/
BuffStatus CBuff_push(CBuff *me, char c);

BuffStatus CBuff_pushString(CBuff *me, const char *str);
BuffStatus CBuff_pushRomString(CBuff *me, const far rom char *str);
 
/*************************************************************************//** 
 * Extrae un byte del Buffer Circular.
 *
 * @param[in]    me				This
 * @param[out]   *c				puntero al destino del byte leido (by ref)
 *
 * @returns      BuffStatus		Estado del buffer
 * @code Ejemplo:
 * 		if (CBuff_pop(&cDaqBuff, &a) == BUFF_EMPTY) ...
 * @endcode
 * @related	     CBuff
 ****************************************************************************/
BuffStatus CBuff_pop(CBuff const *me, char *c);

BuffStatus CBuff_popString(CBuff const *me, char *strOut);

/*************************************************************************//** 
 * Llena el buffer del CBuff con 0x00
 *
 * @param[in]    me				This
 * @related	     CBuff
 ****************************************************************************/
void CBuff_clear(CBuff *me);

/*************************************************************************//** 
 * Sube o Baja la flag _dataSetReady
 *
 * @param[in]    me				This
 * @param[in]    dataSetReady	Boolean que fija el nuevo estado de la flag
 * @related	     CBuff
 ****************************************************************************/
void CBuff_set_Ready(CBuff *me, BOOL dataSetReady);

/*************************************************************************//** 
 * Obtiene el estado de lock del buffer (true = Unlocked)
 *
 * @param[in]    me				This
 * @returns      BOOL			Estado de lock del buffer
 * @related	     CBuff
 ****************************************************************************/
BOOL CBuff_isReady(CBuff *me);

/*************************************************************************//** 
 * Obtiene la cantidad de bytes aun no leidos
 *
 * @param[in]    me				This
 * @returns      uint8_t 		Bytes aun lo leidos
 * @related	     CBuff
 ****************************************************************************/
uint8_t CBuff_getBytesToRead(CBuff *me);

/*************************************************************************//** 
 * Obtiene el espacio libre en el buffer
 *
 * @param[in]    me				This
 * @returns      uint8_t 		Bytes disponibles en el buffer
 * @related	     CBuff
 ****************************************************************************/
uint8_t CBuff_getFree(CBuff *me);

END_CLASS


#endif
//

