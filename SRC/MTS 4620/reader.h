//+--------------------------------------------------------------------------+
//|  $Workfile:: reader.h                          $ $Revision:: 4           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 29/02/12 2:05p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/reader.h                                 $
//+--------------------------------------------------------------------------+
//! @file Reader.h
//! ### Lector del buffer UART. 

#ifndef READER_H_
#define READER_H_

#include "typedefs.h"
#include "CBuff.h"


/** Posibles resultados al finalizar la lectura del puerto 
	@related Reader */ 
typedef enum {
	OK,				///< Se recibe un EOL al final del string antes de Timeout sin llegar a BufferFull
	TIMEOUT,		///< Se produce timeout antes de EOL o Buffer Full
	BUFFER_FULL		///< Se completa el buffer antes de EOL o Timeout
} ReaderRc;


/** Debe definirse un Event Handler en main() para controlar el evento
	de lectura finalizada del buffer de recepción 
	@related Reader */
typedef void (*ReaderEventHandler)(ReaderRc);


/*************************************************************************//** 
 * ##Lector del buffer UART. 
 *  \author    Marcelo A. Valdéz
 *  \copyright FAdeA - Córdoba
 *  \note Todos los campos deben considerarse PRIVATE. Sólo deben accederse 
 *        mediante el constructor y metodos accesors.
 ****************************************************************************/
CLASS(Reader)							    
	CBuff *_cBuff;		
	char *_eolChars;	///< Indicar los char que representan final de línea
	uint8_t _eolCharsSize; ///< Tamaño del array de caracteres eol
	uint16_t _timeOut;	///< Indicar espera máxima antes de generar TIMEOUT
	BOOL _ready;		///< Recepción lista para ser leída
	ReaderEventHandler _onStringReceived;  	///< Controlador de Evento cuando llega eol
	uint16_t _tmr;		///< temporizador interno para timeout
	uint8_t _st;		///< estado interno de la máquina de recepcion
METHODS

/*************************************************************************//** 
 * Constructor del Reader. Asigna propiedades y evento onStringReceived.
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
				DIM(eols), 
				READER_TIMEOUT,
				onDatasetReady);    
 * @endcode
 * @related	    Reader
 ****************************************************************************/
	void Reader_ctor(	Reader *me,
						CBuff *cBuff,
						char *eolChars,
						uint8_t eolCharsSize,
						uint16_t timeOut,
						ReaderEventHandler onStringReceived);
	
/*************************************************************************//** 
 * Constructor - Objeto ejemplo (instanciación automatica)
 * Utiliza una instancia y un CBuff aCBuff alocados automaticamente desde reader.c
 * aCBuff es construido dentro del theReader_ctor() usando un buffer de 255 chars
 * alocados también desde reader.c
 * Si sólo se necesita un reader (lectura por un solo puerto UART), se recomienda
 * utilizar este objeto. En caso de necesitar otro puerto UART, deberá alocarse
 * manualmente un CBuff y pasar un puntero del mismo a Reader_ctor().
 * @param[in]    eolChars	set de caracteres que seran considerados como \b eol
 * @param[in]    eolCharsSize	Longitud de eolChars (usar DIM())
 * @param[in]    timeout	tiempo de espera sin recibir caracteres antes de enviar Timeout
 * @param[in]    onStringReceived	Handler de evento StringReceived, que se 
 *               dispara al finalizar la lectura por EOL, Timeout o BufferFull
 * @code EJEMPLO:
 				theReader_ctor(	eols,
								DIM(eols), 
								READER_TIMEOUT,
								onDatasetReady);    
 * @endcode
 * @related	    Reader
 ****************************************************************************/
	void theReader_ctor(char *eolChars,
						uint8_t eolCharsSize,
						uint16_t timeOut,
						ReaderEventHandler onStringReceived);
						
/*************************************************************************//** 
 * Iniciar la captura de bytes desde la Uart
 * @param[in]    me			This
 * @related	     Reader
 ****************************************************************************/
	void Reader_start(Reader *me);
	
/*************************************************************************//** 
 * Detener la captura de bytes
 * @param[in]    me			This
 * @related	     Reader
 ****************************************************************************/
	void Reader_stop(Reader *me);


/*************************************************************************//** 
 * Copia el string leido en un buffer especificado por el usuario
 * @param[in]    me			This
 * @param[out]	 outBuff	Buffer de salida
 * @related	     Reader
 ****************************************************************************/
	void Reader_read(Reader *me, char* outBuff);

/*************************************************************************//** 
 * Limpiar el buffer circular. Rellenarlo con 0x00
 * @param[in]    me			This
 * @related	     Reader
 ****************************************************************************/
	void Reader_clearBuff(Reader *me);
	
/*************************************************************************//** 
 * Actualizar el contador de TIMEOUT (desde TMR0 ISR)
 * @param[in]    me			This
 * @related	     Reader
 ****************************************************************************/
	void Reader_update(Reader *me);
	
/*************************************************************************//** 
 * Almacenar byte desde la UART (desde RCIF ISR)
 * @param[in]    me			This
 * @param[in]    data		byte recibido desde la UART (TXREG)
 * @related	     Reader
 ****************************************************************************/
	void Reader_push(Reader *me, char data);
	

END_CLASS

extern Reader theReader;  // ver CONSTRUCTOR en reader.c
extern CBuff  aCBuff;

						
#define theReader_start()		Reader_start(&theReader)
#define theReader_stop()		Reader_stop(&theReader)
#define theReader_read(outBuff)	Reader_read(&theReader, (outBuff))
#define theReader_clearBuff()	Reader_clearBuff(&theReader)
#define theReader_update()		Reader_update(&theReader)
#define theReader_push(data)	Reader_push(&theReader, (data))

#endif
//
