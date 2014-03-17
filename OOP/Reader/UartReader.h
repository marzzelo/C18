//+--------------------------------------------------------------------------+
//|  $Workfile:: UartReader.h                          $ $Revision:: 14      $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 13/01/12 9:29a                                               $
//|  $Archive:: /@C18/SRC/MTS/UartReader.h                                   $
//+--------------------------------------------------------------------------+
/*! @file UartReader.h
 */

#ifndef UARTREADER_H_
#define UARTREADER_H_

#include "typedefs.h"
#include "CBuff.h"



/** Posibles resultados al finalizar la lectura del puerto 
	@related UartReader */ 
typedef enum {
	OK,				///< Se recibe un EOL al final del string antes de Timeout sin llegar a BufferFull
	TIMEOUT,		///< Se produce timeout antes de EOL o Buffer Full
	BUFFER_FULL		///< Se completa el buffer antes de EOL o Timeout
} ReaderRc;


/** Debe definirse un Event Handler en main() para controlar el evento
	de lectura finalizada del buffer de recepción 
	@related UartReader */
typedef void (*ReaderEventHandler)(ReaderRc);


/*************************************************************************//** 
 * Lector del buffer UART. Several species of small furry animals gathered 
 * together in a cave and grooving with a pict.
 *  \author    Marcelo A. Valdéz
 *  \copyright FAdeA - Córdoba
 *  \note Todos los campos deben considerarse PRIVATE. Sólo deben accederse 
 *        mediante el constructor y metodos accesors.
 ****************************************************************************/
CLASS(UartReader)							    
	CBuff *_cBuff;		///< Debe proporcionarse un buffer UART
	char *_eolChars;	///< Indicar los char que representan final de línea
	uint8_t _eolCharsSize; ///< Tamaño del array de caracteres eol
	uint16_t _timeOut;	///< Indicar espera máxima antes de generar TIMEOUT
	BOOL _ready;		///< Recepción lista para ser leída
	ReaderEventHandler _onStringReceived;  	///< Controlador de Evento cuando llega eol
	uint16_t _tmr;		///< temporizador interno para timeout
	uint8_t _st;		///< estado interno de la máquina de recepcion
METHODS

/*************************************************************************//** 
 * Constructor del UartReader. Asigna propiedades y evento onStringReceived.
 * @param[in]    me			This
 * @param[in]    CBuff		Buffer Circular de recepcion UART (debe instanciarse previamente)
 * @param[in]    eolChars	set de caracteres que seran considerados como \b eol
 * @param[in]    eolCharsSize	Longitud de eolChars (usar DIM())
 * @param[in]    timeout	tiempo de espera sin recibir caracteres antes de enviar Timeout
 * @param[in]    onStringReceived	Handler de evento StringReceived, que se dispara al finalizar la lectura por EOL, Timeout o BufferFull
 *
 * @code EJEMPLO:
 				Reader_ctor(&reader1, 
				rxBuff, 
				eols,
				DIM(rxBuff), 
				READER_TIMEOUT,
				onDatasetReady);    
 * @endcode
 * @related	    UartReader
 ****************************************************************************/
	void UartReader_ctor(	UartReader *me,
						CBuff *cBuff,  
						char *eolChars,
						uint8_t eolCharsSize,
						uint16_t timeOut,
						ReaderEventHandler onStringReceived);
	
/*************************************************************************//** 
 * Iniciar la captura de bytes desde la Uart
 * @param[in]    me			This
 * @related	     UartReader
 ****************************************************************************/
	void UartReader_start(UartReader *me);
	
/*************************************************************************//** 
 * Detener la captura de bytes
 * @param[in]    me			This
 * @related	     UartReader
 ****************************************************************************/
	void UartReader_stop(UartReader *me);

/*************************************************************************//** 
 * Limpiar el buffer circular. Rellenarlo con 0x00
 * @param[in]    me			This
 * @related	     UartReader
 ****************************************************************************/
	void UartReader_clearBuff(UartReader *me);
	
/*************************************************************************//** 
 * Actualizar el contador de TIMEOUT (desde TMR0 ISR)
 * @param[in]    me			This
 * @related	     UartReader
 ****************************************************************************/
	void UartReader_update(UartReader *me);
	
/*************************************************************************//** 
 * Almacenar byte desde la UART (desde RCIF ISR)
 * @param[in]    me			This
 * @param[in]    data		byte recibido desde la UART (TXREG)
 * @related	     UartReader
 ****************************************************************************/
	void UartReader_push(UartReader *me, char data);
	

END_CLASS

extern UartReader theUartReader;
#define theUartReader_ctor(cBuff, eolChars, eolCharsSize, timeOut, onStringReceived) \
		UartReader_ctor(&theUartReader, (cBuff), (eolChars), (eolCharsSize), (timeOut), (onStringReceived))
#define theUartReader_start()	UartReader_start(&theUartReader)
#define theUartReader_stop()	UartReader_stop(&theUartReader)
#define theUartReader_clearBuff()	UartReader_clearBuff(&theUartReader)
#define theUartReader_update()	UartReader_update(&theUartReader)
#define theUartReader_push(data)	UartReader_push(&theUartReader, (data))

#endif
