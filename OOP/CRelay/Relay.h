//+--------------------------------------------------------------------------+
//|  $Workfile:: relay.h                           $ $Revision:: 3           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/09/13 8:51                                                $
//|  $Archive:: /@C18/SRC/LATCH2/relay.h                                     $
//+--------------------------------------------------------------------------+
//! \file Relay.h
//!  ### Genera ciclos Ton Toff en un pin de puerto IO con ciclo de trabajo programable


#ifndef RELAY_H_
#define RELAY_H_


#include "typedefs.h"

typedef enum _RelayState {
	IDLE,
	COUNTING_ON,
	COUNTING_OFF
} RelayState;

typedef void (*RelayHandler)(uint8_t);

/** ## Relay.
    1. Al cumplirse Ton se apaga el pin correspondiente y se inicia Toff
    2. Al cumplirse Toff se enciende el pin, se inicia Ton y se incrementa el contador de ciclos
    3. Al llegar el contador a los ciclos especificados, se detiene el ciclado.
    4. Si se especifica 0 ciclos, el ciclado no se detiene hasta recibir el mensaje stop()
    5. Para iniciar el ciclado, debe emitirse el mensaje start()

    
*/
CLASS(Relay)
	uint8_t _id;
	uint16_t _Ton;			///< Periodo en ON
	uint16_t _Toff;			///< Periodo en OFF
	uint16_t _cycles;		///< Cantidad de ciclos a realizar, 0 = continuo
	uint16_t _t;			///< Temporizador
	uint16_t _c;			///< Contador ciclos
	RelayState _state;
	BOOL _enabled;			///< update?
	BOOL _instantiated;		///< constructor called?
	RelayHandler _onStartTon;		///< Se lanza al comenzar cada ciclo Ton
	RelayHandler _onStartToff; 		///< Se lanza al comenzar cada ciclo Toff
	RelayHandler _onCyclesCompleted; ///< Se lanza al terminar el ciclado
	BOOL _startHI;			///< Se inicia ACTIVO (FALSE: Se inicia INACTIVO)
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase. 
 ****************************************************************************/
	Relay *Relay_ctor(Relay *me,
	 				  uint8_t id,
					  uint16_t Ton, 
					  uint16_t Toff,
					  uint16_t cycles,
					  RelayHandler onStartTon,
					  RelayHandler onStartToff,
					  RelayHandler onCyclesCompleted,
					  BOOL startHI);

/*************************************************************************//** 
 * Inicia el conteo de tiempo 
 ****************************************************************************/						  
	void Relay_start(Relay *me);

/*************************************************************************//** 
 * Detiene el conteo de tiempo y resetea estado y contadores internos
 ****************************************************************************/
	void Relay_stop(Relay *me);
	
	
/*************************************************************************//** 
 * + Actualiza el contador interno de tiempo. 
 ****************************************************************************/	
	void Relay_update(Relay *me);

/*************************************************************************//** 
 * Detiene/reinicia la actualización sin modificar estado ni variables internas
 ****************************************************************************/
	void Relay_pause(Relay *me);
	void Relay_resume(Relay *me);
	
	
END_CLASS

#endif


//
