//+--------------------------------------------------------------------------+
//|  $Workfile:: TBase.h                           $ $Revision:: 16          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 29/02/12 3:06p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/TBase.h                                  $
//+--------------------------------------------------------------------------+
//! \file TBase.h
//!  ### Temporizador con eventos.


#ifndef TBASE_H_
#define TBASE_H_

#include "typedefs.h"

/** ## Temporizador.
    Al cumplirse el tiempo especificado en **dt**, se genera el evento **onTimeElapsed()**
	y se detiene el conteo. Al terminar los ciclos especificados en \b nTicks
	se genera el evento **onTicksDone()**.
	+ Luego de llamar al constructor, enviar start()
	+ Puede cancelarse el conteo con stop()
	+ Debe colocarse update() en la ISR de algun temporizador (ej.: 1ms) */
CLASS(TBase)
	uint16_t _dt;		///< Periodo de muestreo por canal
	uint16_t _t;		///< Temporizador de uso interno
	uint16_t _nTicks;	///< Cantidad de muestras antes de detenerse
	uint16_t _nS;		///< Contador de muestras finalizadas
	BOOL _enabled;		///< update timer?
	EventHandler _onTimeElapsed;	///< EventHandler para cada muestra finalizada
	EventHandler _onTicksDone; 		///< EH para nTicks finalizados
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase. 
 * @param[in]    me			This
 * @param[in]    dt			Periodo de muestreo
 * @param[in]    nTicks	Samples per channel
 * @param[in]    onTimeElapsed Controlador de evento Muestreo finalizado
 * @param[in]    onTicksDone Controlador de evento nTicks completados
 * @returns      Puntero al objeto This
 *
 * @code         Código de prueba    
 *				 TBase_ctor(&myDelay, 
 *							  PERIOD,
 *							  NSAMPLES_PER_CHANNEL,
 *							  onTimeOut,
 *							  onTicksDone);
 * @endcode
 * @note		 Para adquisición continua, pasar 0x00 como nTicks/channel
 * @related		 TBase
 ****************************************************************************/
	TBase *TBase_ctor(TBase *me, 
						  uint16_t dt, 
						  uint16_t nTicks,
						  EventHandler onTimeElapsed,
						  EventHandler onTicksDone);

/*************************************************************************//** 
 * Inicia el conteo de tiempo (muestreo). Al finalizar cada periodo, genera el evento
 * onTimeElapsed.
 * @param[in]    me			This
 *
 * @code         Código de prueba    
 *				 TBase_start(&myDelay);
 * @endcode
 * @related		 TBase
 ****************************************************************************/						  
	void TBase_start(TBase *me);

/*************************************************************************//** 
 * Detiene el conteo de tiempo (muestreo). No se genera el evento onTimeElapsed.
 * @param[in]    me			This
 *
 * @code         Código de prueba    
 *				 TBase_stop(&myDelay);
 * @endcode
 * @related		 TBase
 ****************************************************************************/
	void TBase_stop(TBase *me);
	
/*************************************************************************//** 
 * Especifica el intervalo de temporización (periodo de muestreo)
 * @param[in]    me			This
 * @param[in]    dt			periodo de muestreo en [ms] (debe ser superior al número 
 *  						de canales activos por el tiempo de adquisición más
 *							el tiempo de conversión). 
 *
 * @code         Código de prueba    
 *				 TBase_set_dt(&myDelay, 100);
 * @endcode
 * @related		 TBase
 ****************************************************************************/	
	TBase *TBase_set_dt(TBase *me, uint16_t dt);

/*************************************************************************//** 
 * Especifica el número de ciclos de timeout a generar (muestras por canal)
 * @param[in]    me			This
 * @param[in]    nTicks	Cantidad de muestras por canal a tomar (timeOuts)
 *
 * @code         Código de prueba    
 *				 TBase_set_nTicks(&myDelay, 0);
 * @endcode
 * @note		 Para realizar adquisición contínua, pasar 0 como nTicks
 * @related		 TBase
 ****************************************************************************/	
	TBase *TBase_set_nTicks(TBase *me, uint16_t nTicks);
	
/*************************************************************************//** 
 * Actualiza el contador interno de tiempo. Debe correr en ISR cada 1ms
 * @param[in]    me			This
 * @note		 Los controladores de evento son llamados desde foreground (ISR)
 *				 por lo que no pueden contener instrucciones printf() ni operaciones
 *				 que requieran tiempos cercanos a 1ms
 * @related		 TBase
 ****************************************************************************/	
	void TBase_update(TBase *me);

	
END_CLASS

#endif


//	#TBase box TimeBase [label="_nS = _nTicks\n_t = _dt\n_enabled = TRUE"];
// 	#TBase box TimeBase [label="dt\nnTicks\nonTimeElapsed\nonTicksDone"];
//	hscale ="1.5";
//	Cont,TimeBase,IntSR;
//	Cont->TimeBase [label="TBase_ctor()"];
//	Cont->TimeBase [label="TBase_start()"];
//	TimeBase box TimeBase [label="_nS = _nTicks"
