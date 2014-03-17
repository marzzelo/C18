//+--------------------------------------------------------------------------+
//|  $Workfile:: Timer.h                           $ $Revision:: 4           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 16/08/13 10:08                                               $
//|  $Archive:: /@C18/OOP/Timer/Timer.h                                      $
//+--------------------------------------------------------------------------+
//! \file Timer.h
//!  ### Temporizador con eventos..


#ifndef TIMER_H_
#define TIMER_H_

#include "typedefs.h"

/** ## Temporizador.
    1. Al cumplirse el tiempo especificado en **dt**, se genera el evento **onTimeElapsed()**
	y se detiene el conteo. 
	2. Al terminar los ciclos especificados en `nTicks`
	se genera el evento **onTicksDone()**.
	+ Luego de llamar al constructor, se debe enviar **start()**
	+ El segundo parámetro del ctor es un puntero al objeto contenedor. Este puntero
	es devuelto como parámetro de salida en los eventos para permitir identificar al 
	destinatario del evento.
	+ Puede cancelarse el conteo con **stop()**
	+ Para sacar un valor constante, utilizar la macro **LCD_set()**
	+ Debe colocarse **Timer_update()** en la ISR de algun temporizador (ej.: 1ms) */
CLASS(Timer)
	void *_parent;			///< Objeto contenedor
	uint16_t _dt;			///< Periodo de muestreo por canal
	uint16_t _t;			///< Temporizador de uso interno
	uint16_t _nTicks;		///< Cantidad de muestras antes de detenerse
	uint16_t _nS;			///< Contador de muestras finalizadas
	BOOL _enabled;			///< update timer?
	Handler _onTimeElapsed;	///< EventHandler para cada muestra finalizada
	Handler _onTicksDone; 	///< EH para nTicks finalizados
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase. 
 * @param[in]    me			This
 * @param[in]    parent		contenedor del Timer
 * @param[in]    dt			Periodo de muestreo
 * @param[in]    nTicks		Samples per channel
 * @param[in]    onTimeElapsed Controlador de evento Muestreo finalizado
 * @param[in]    onTicksDone Controlador de evento nTicks completados
 * @returns      Puntero al objeto me
 *
 * @code         Código de prueba    
 *				 Timer_ctor(  &myTimer, 
 *							  me,			// puntero al objeto contenedor
 *							  PERIOD,
 *							  NSAMPLES_PER_CHANNEL,
 *							  onTimeOut,
 *							  onTicksDone);
 * @endcode
 * @note		 Para adquisición continua, pasar 0x00 como nTicks/channel
 * @related		 Timer
 ****************************************************************************/
	Timer *Timer_ctor(Timer *me, 
					  void *parent,
					  uint16_t dt, 
					  uint16_t nTicks,
					  Handler onTimeElapsed,
					  Handler onTicksDone);

/*************************************************************************//** 
 * Inicia el conteo de tiempo (muestreo). Al finalizar cada periodo, genera el evento
 * onTimeElapsed.
 * @param[in]    me			This
 *
 * @code         Código de prueba    
 *				 Timer_start(&myDelay);
 * @endcode
 * @related		 Timer
 ****************************************************************************/						  
	void Timer_start(Timer *me);

/*************************************************************************//** 
 * Detiene el conteo de tiempo (muestreo). No se genera el evento onTimeElapsed.
 * @param[in]    me			This
 *
 * @code         Código de prueba    
 *				 Timer_stop(&myDelay);
 * @endcode
 * @related		 Timer
 ****************************************************************************/
	void Timer_stop(Timer *me);
	
/*************************************************************************//** 
 * Especifica el intervalo de temporización (periodo de muestreo)
 * @param[in]    me			This
 * @param[in]    dt			periodo de muestreo en [ms] (debe ser superior al número 
 *  						de canales activos por el tiempo de adquisición más
 *							el tiempo de conversión). 
 *
 * @code         Código de prueba    
 *				 Timer_set_dt(&myDelay, 100);
 * @endcode
 * @related		 Timer
 ****************************************************************************/	
	Timer *Timer_set_dt(Timer *me, uint16_t dt);

/*************************************************************************//** 
 * Especifica el número de ciclos de timeout a generar (muestras por canal)
 * @param[in]    me			This
 * @param[in]    nTicks	Cantidad de muestras por canal a tomar (timeOuts)
 *
 * @code         Código de prueba    
 *				 Timer_set_nTicks(&myDelay, 0);
 * @endcode
 * @note		 Para realizar adquisición contínua, pasar 0 como nTicks
 * @related		 Timer
 ****************************************************************************/	
	Timer *Timer_set_nTicks(Timer *me, uint16_t nTicks);
	
/*************************************************************************//** 
 * + Actualiza el contador interno de tiempo. 
 * + Debe correr en ISR cada 1ms.
 *
 * #Eventos
 *
 * @code 		 me->_onTimeElapsed(me->_parent)			@endcode
 *
 * Se genera ciclicamente según itervalo especificado en **dt**
 *
 * @code 		 me->_onTicksDone(me->_parent)			@endcode
 *
 * Se genera por única vez al concluir el número de ciclos especificados en **nTicks**
 * 
 * ---
 *
 * @param[in]    me			This
 * @note		 Los controladores de evento son llamados desde foreground (ISR)
 *				 por lo que no pueden contener instrucciones printf() ni operaciones
 *				 que requieran tiempos cercanos a 1ms
 * @related		 Timer
 ****************************************************************************/	
	void Timer_update(Timer *me);

	
END_CLASS

#endif


//	#Timer box TimeBase [label="_nS = _nTicks\n_t = _dt\n_enabled = TRUE"];
// 	#Timer box TimeBase [label="dt\nnTicks\nonTimeElapsed\nonTicksDone"];
//	hscale ="1.5";
//	Cont,TimeBase,IntSR;
//	Cont->TimeBase [label="Timer_ctor()"];
//	Cont->TimeBase [label="Timer_start()"];
//	TimeBase box TimeBase [label="_nS = _nTicks"
