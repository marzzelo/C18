//+--------------------------------------------------------------------------+
//|  $Workfile:: CLeds.h                           $ $Revision:: 14          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 3/04/12 12:19p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/CLeds.h                                  $
//+--------------------------------------------------------------------------+
//! \file CLeds.h
//!  ### Control de array de 8 leds en un puerto de 8 bits.

#ifndef CLEDS_H_
#define CLEDS_H_

#include "typedefs.h"
#include "Timer.h"

typedef uint8_t (*LedSequence)(void);
 
/*************************************************************************//** 
 * ##Control de array de 8 leds en un puerto de 8 bits.
 * Controla los leds automáticamente según la secuencia fijada por una función
 * delegada pasada como parámetro en el constructor.
 * Esta función debe devolver un `uint8_t` cada vez que es llamada. El estado
 * puede guardarse en una var estatica o implementarse como una FSM.
 * El parámetro dt establece el tiempo en [ms] entre llamadas a esta función. 
 * El parámetro nTicks fija la cantidad de veces que será llamada la función.
 * Al finalizar los nTicks, se genera el evento `onLedsDone()` que debe devolver
 * un uint8_t con el estado deseado final del array.
 * @note		Si no se utiliza el sigleton _theLeds_, las secuencias serán 
 *				iguales para todos los objetos instanciados.
 * 
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 ****************************************************************************/

CLASS(CLeds)
	Timer _ledTimer;						  ///< base de tiempos (uso interno)
	port_t  *_ledPort;				  				///< PORTD para el singleton
	uint16_t _dt;									///< periodo de la secuencia
	uint16_t _nTicks;					  ///< cantidad de llamadas a sequence()
	uint8_t *_array;					///< Array con la secuencia de encendido
	uint8_t _arraySize;						 ///< Tamaño del array de secuencias
	LedSequence _sequence;  		     ///< secuencia de encendido de los leds
	LedSequence _onLedsDone;  		       ///< evento de finalización de nTicks
	EventHandler _onArrayCycle;	 ///< se genera al ciclar el array de secuencias
	BOOL _isModeSeq;				 ///< Modo secuencial? (secuencia calculada)
	uint8_t _index;						 ///< Posición en el array de secuencias

METHODS

/*************************************************************************//** 
 * Constructor.
 * Establece la secuencia, periodo y cantidad de pasos totales. Establece todos
 * los bits del registro TRISx como SALIDAS DIGITALES, basandose en la suposicion
 * TRISx = PORTx + 18.
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 * @param[in]   ledPort		PUNTERO al Puerto del array de leds (ej.: &PORTD)
 * @param[in]   dt			periodo de la secuencia
 * @param[in]   nTicks		Cantidad de pasos de la secuencia
 * @param[in]   sequence	puntero a función que devuelve la secuencia deseada
 * @param[in]   onLedsDone	EventHandler que fija el estado final del array de leds
 * @returns     Puntero a This
 * @code        CLeds_ctor(&theLeds, &PORTD, 500, 1000, seq, onLedsDone);
 * @endcode
 * @related     CLeds
 ****************************************************************************/
	CLeds *CLeds_ctor(CLeds *me,
			port_t *ledPort,
			uint16_t dt, 
			uint16_t nTicks, 
			LedSequence sequence,
			LedSequence onLedsDone);
					
	void CLeds_arrayModeSetup(
						CLeds *me, 
						uint8_t *array,
						uint8_t arraySize,
						EventHandler onArrayCycle);
			
	void CLeds_set_dt(CLeds *me, uint16_t dt);
	void CLeds_set_nTicks(CLeds *me, uint16_t nTicks);

/*************************************************************************//** 
 * Start Secuencial. Inicia la secuencia en modo calculado (a través de
 *					 callbacks a la función sequence())
 * @code        CLeds_startSeq(&theLeds);    @endcode
 * @related     CLeds
 ****************************************************************************/
	void CLeds_startSeq(CLeds *me);
	
/*************************************************************************//** 
 * Start con Array. Inicia la secuencia en modo Array (La secuencia es dada
 *					por los elementos de un array)
 * @code        CLeds_startArray(&theLeds);    @endcode
 * @related     CLeds
 ****************************************************************************/	
	void CLeds_startArray(CLeds *me);
	
/*************************************************************************//** 
 * Stop. Detiene la secuencia en el array de leds.
 * @code        CLeds_stop(&theLeds);    @endcode
 * @related     CLeds
 ****************************************************************************/	
	void CLeds_set(CLeds *me, uint8_t value);  
	void CLeds_pause(CLeds *me);
	
/*************************************************************************//** 
 * Cambio de secuencia. Establece una nueva función para la secuenciación.
 * @code        CLeds_newSequence(&theLeds, barrido_izq, 0);    @endcode
 * @related     CLeds
 ****************************************************************************/	
	void CLeds_newSequence(CLeds *me, LedSequence newSequence, uint16_t nTicks);
	
/*************************************************************************//** 
 * ISR Updater. Actualiza el estado de los leds
 * @note		Debe llamarse cada 1ms 
 * @code        CLeds_update(&theLeds);    @endcode
 * @related     CLeds
 ****************************************************************************/	
	void CLeds_update(CLeds *me);	// ISR 1ms
END_CLASS

#define CLeds_stop(me) 		CLeds_set((me), 0x00) ;
#endif
