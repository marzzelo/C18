//+--------------------------------------------------------------------------+
//|  $Workfile:: Fsm.h                               $ $Revision:: 4         $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 18/06/11 11:12p                                              $
//|  $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/Fsm.h              $
//+--------------------------------------------------------------------------+


#ifndef FSM_H_
#define FSM_H_

#include "typedefs.h"


typedef void (*EventHandler)(void);


/* 
==============================================================================
FSM de n estados.
- Cada estado espera un tiempo t0[i] y luego ejecuta el Handler eh[i], para
pasar luego al siguiente estado.
- Al terminar, se detiene automáticamente, hasta recibir el mensaje start()
- Puede forzarse la detención enviando stop()
- El método update() debe llamarse en la ISR de algún temporizador.
==============================================================================
 */
CLASS(Fsm)
	EventHandler eh[5];
	uint16_t t0[5];
	uint16_t t;
	uint8_t nStates;
	uint8_t st;
	uint8_t rep;
	
METHODS

/*************************************************************************//** 
 * Constructor de la máquina de estados
 * @param[in]    me			objeto a construir. Debe instanciarse en main()  
 * @param[in]    nStates	cantidad de estados de la máquina
 * @param[in]    t0[]		array con los delays de cada estado
 * @param[in]    eh[]		array con los handlers a ejecutar en cada estado
 * @returns      Fsm*		puntero a la Fsm inicializada
 * @test         Fsm_ctor(&myFsm, 3, myT0s, myEhs);
 ****************************************************************************/
	Fsm *Fsm_ctor(Fsm *me, uint8_t nStates, uint16_t t0[], const EventHandler eh[]);

	void Fsm_start(Fsm *me, uint16_t rep);
	void Fsm_stop(Fsm *me);
	void Fsm_update(Fsm *me);
	
END_CLASS

#endif
