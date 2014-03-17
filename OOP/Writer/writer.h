//+--------------------------------------------------------------------------+
//|  $Workfile:: writer.h                          $ $Revision:: 5           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 14/03/12 8:55a                                               $
//|  $Archive:: /@C18/SRC/Explorer1/writer.h                                 $
//+--------------------------------------------------------------------------+
//! \file writer.h
//! ### Envía strings a la UART.

#ifndef WRITER_H_
#define WRITER_H_

#include "typedefs.h"


/*************************************************************************//** 
 * ## Envía strings a la UART. 
 * Utiliza un buffer lineal de caracteres, que se sobreescribe por completo 
 * luego de cada envío.
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 ****************************************************************************/
CLASS(Writer)
	char *_wbuff;
	BOOL _enabled;
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase.
 * @param[in]   wbuff  	buffer de escritura, char*
 * @returns     this
 * @code        Writer_ctor(&theWriter, theBuff)   @endcode
 * @related     Writer
 ****************************************************************************/
	Writer *Writer_ctor(Writer *me, char *wbuff);

/*************************************************************************//** 
 * Comienza a chequearse el buffer del Writer. Si hay un string, se envía a la
 * UART mediante xputsUART() y se borra el string colocando 0x00 en wbuff[0].
 * @code        Writer_start(&theWriter)   @endcode
 * @related     Writer
 ****************************************************************************/
	void Writer_start(Writer *me);
	
/*************************************************************************//** 
 * Detiene el chequeo del buffer del Writer. 
 * @code        Writer_stop(&theWriter)   @endcode
 * @related     Writer
 ****************************************************************************/	
	void Writer_stop(Writer *me);
	
/*************************************************************************//** 
 * Chequea el buffer. Si hay un string, lo envía a la UART. 
 * @caution		Este método debe utilizarse en el thread principal (main())
 * @code        Writer_update(&theWriter)   @endcode
 * @related     Writer
 ****************************************************************************/	
	void Writer_update(Writer *me);
	
/*************************************************************************//** 
 * Copia un string desde la RAM en el buffer del Writer, que es enviado 
 * inmediatamente por Writer_update()
 * @code        theWriter_putString(strHelloworld);   @endcode
 * @related     Writer
 ****************************************************************************/	
	void Writer_putString(Writer *me, char *str);
	
/*************************************************************************//** 
 * Copia un string desde la FLASH en el buffer del Writer, que es enviado 
 * inmediatamente por Writer_update() 
 * @code        theWriter_putrString((frchar*)"Hello World!");   @endcode
 * @related     Writer
 ****************************************************************************/		
	void Writer_putrString(Writer *me, frchar *str);
	
END_CLASS

/** Singleton para el caso de utilizar un único puerto serie */
extern Writer theWriter;	// singleton
extern char theBuff[];

#define theWriter_ctor()			Writer_ctor(&theWriter, theBuff)
#define theWriter_start()			Writer_start(&theWriter)
#define theWriter_update()			Writer_update(&theWriter)
#define theWriter_putString(str) 	Writer_putString(&theWriter, (str))
#define theWriter_putrString(str) 	Writer_putrString(&theWriter, (str))

#endif
//
