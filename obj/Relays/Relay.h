//+--------------------------------------------------------------------------+
//|  $Workfile:: Relay.h                           $ $Revision:: 10          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 20/09/13 10:02                                               $
//|  $Archive:: /@C18/SRC/LATCH2/Relay.h                                     $
//+--------------------------------------------------------------------------+
//! \file Relay.h
//!  ### Genera ciclos Ton Toff en un pin de puerto IO con ciclo de trabajo programable


#ifndef RELAY_H_
#define RELAY_H_


#include "typedefs.h"

typedef enum _RelayState {
	IDLE,
	DELAYING,
	COUNTING_ON,
	COUNTING_OFF
} RelayState;


// FLAGS	
	#define _ENABLED		_flags.b0		
	#define _PAUSED			_flags.b1
	#define _STARTS_HI		_flags.b2		

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
	uint16_t _offset;		///< delay inicial
	uint16_t _cycles;		///< Cantidad de ciclos a realizar, 0 = continuo
	uint16_t _t;			///< Temporizador
	uint16_t _c;			///< Contador ciclos restantes
	RelayState _state;
	BYTE _flags;
	RelayHandler _onStartTon;		///< Se lanza al comenzar cada ciclo Ton
	RelayHandler _onStartToff; 		///< Se lanza al comenzar cada ciclo Toff
	RelayHandler _onCyclesCompleted; ///< Se lanza al terminar el ciclado
	
	
METHODS
/*************************************************************************//** 
 * Constructor de la clase. 
 ****************************************************************************/
	Relay *Relay_ctor(Relay *me,
	 				  uint8_t id,
					  uint16_t Ton, 
					  uint16_t Toff,
					  uint16_t offset,
					  uint16_t cycles,
					  RelayHandler onStartTon,
					  RelayHandler onStartToff,
					  RelayHandler onCyclesCompleted,
					  BOOL startsHI);

/*************************************************************************//** 
 * Inicia el conteo de tiempo 
 ****************************************************************************/						  
	void Relay_cstart(Relay *me, uint16_t inicnt, uint16_t coffset) ;

#define Relay_istart(me, inicnt) Relay_cstart((me), (inicnt), (me)->_offset)
#define Relay_start(me) 		 Relay_cstart((me), 0, (me)->_offset)

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
