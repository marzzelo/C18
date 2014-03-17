//+--------------------------------------------------------------------------+
//|  $Workfile:: UartWriter.h                          $ $Revision:: 14      $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 14/03/12 1:29p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/UartWriter.h                             $
//+--------------------------------------------------------------------------+
//! \file UartWriter.h
//! \brief Envía caracteres a la UART desde un buffer circular tipo CBuff


#ifndef UARTWRITER_H_
#define UARTWRITER_H_

#include "typedefs.h"
#include "CBuff.h"

 /*************************************************************************//** 
 * Envía caracteres a la UART desde un buffer circular tipo CBuff
 * No escribe nunca en este buffer (read only). 
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 ****************************************************************************/
CLASS(UartWriter)
	CBuff const *_cbuff;	///< Buffer circular read-only para salida UART
	BOOL _ready2print;		///< Todos los datos han sido enviados
	EventHandler _onBufferEmpty;
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase
 * @param[in]   cbuff	Buffer circular, instanciado e inicializado
 * @param[in]   onBufferEmpty	controlador de evento por Buffer vacío
 * @related		UartWriter
 ****************************************************************************/
	void UartWriter_ctor(UartWriter *me, CBuff const *cbuff, EventHandler onBufferEmpty);

/*************************************************************************//** 
 * Cambia el buffer de lectura del Writer
 * @param[in]   cbuff	Buffer circular, instanciado e inicializado
 * @related		UartWriter
 ****************************************************************************/
	void UartWriter_set_cBuff(UartWriter *me, CBuff const *cbuff);

/*************************************************************************//** 
 * Inicia el chequeo de los datos para enviar a la UART. Si el buffer está vacío, 
 * genera onBufferEmpty() por cada intento.
 * @related		UartWriter
 ****************************************************************************/
	void UartWriter_start(UartWriter *me);
	
/*************************************************************************//** 
 * Detiene el chequeo de datos para enviar a la UART. 
 * @related		UartWriter
 ****************************************************************************/
	void UartWriter_stop(UartWriter *me);	
	
/*************************************************************************//** 
 * Chequea la existencia de datos en el buffer de salida. 
 * @note		DEBE LLAMARSE DESDE BACKGROUND (main())
 * @related		UartWriter
 ****************************************************************************/
	void UartWriter_update(UartWriter *me);  /* BACKGROUND!!! */
	
END_CLASS


/***************************************
 *                                     * 
 *           S I N G L E T O N         *
 *                                     *
 ***************************************/
extern 	UartWriter theUartWriter;

#define theUartWriter_ctor(pcbuff, onBufferEmpty) \
		UartWriter_ctor(&theUartWriter, (pcbuff), (onBufferEmpty))
#define theUartWriter_set_cBuff(cbuff)	UartWriter_set_cBuff(&theUartWriter, (cbuff))
#define theUartWriter_start()			UartWriter_start(&theUartWriter)
#define theUartWriter_stop()			UartWriter_stop(&theUartWriter)
#define theUartWriter_update()			UartWriter_update(&theUartWriter)

#endif
