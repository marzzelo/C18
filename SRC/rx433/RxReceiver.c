//+--------------------------------------------------------------------------+
//|  $Workfile:: RxReceiver.c                          $ $Revision:: 1       $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 23/12/13 8:40                                                $
//|  $Archive:: /@C18/SRC/rx433/RxReceiver.c                                 $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include "typedefs.h"
#include "RxReceiver.h"
#include "qassert.h"
#include "string.h"

DEFINE_THIS_FILE;

typedef enum RxStatesTag {
	IDLE,
	WAITING_SILENCE,
	WAITING_START,
	VERIFYING_START,
	WAITING_RETZERO,
	WAITING_BIT,
	DECODING_BIT
} RxStates;

/***************************************
 *                                     * 
 *            constructor              *
 *                                     *
 ***************************************/
	void RxReceiver_ctor( 	RxReceiver *me,
							port_t *rxPort,  
							uint8_t rxPinMask,
							EventHandler onStartDetected,
							EventHandler onButtonPressed)
{
	me->_rxPort = rxPort;
	me->_rxPinMask = rxPinMask; 
	me->_onStartDetected = onStartDetected;
	me->_onButtonPressed = onButtonPressed;
	me->_st = IDLE;
} 


/*--------------------------------------------------------------------------*/
void RxReceiver_start(RxReceiver *me)
{
	me->_t = 0;
	me->_tMin = 2;
	me->_tMax = 6;
	me->_st = WAITING_SILENCE;
}//


/*************************************************************************//** 
 * Driver de recepción RF-433MHz 24bits.
 * Debe llamarse desde foreground con alta prioridad (ISR_HI) cada 120us
 * CARACTERISTICAS DE LA SEÑAL:
 *	Tstart = 720us ON = 6T
 *  Tzero = 240us ON = 2T
 *  Tone = 720us ON = 6T
 *  Treturn2zero = 240us OFF
 *	Tsilence = 7200us OFF = 60T
 ****************************************************************************/
 
 /*
 	ESTRATEGIA:
 	(Tsample = 120us)
 	- esperar zero
 	- si llega zero, verificar si alcanza 10T, si no, reiniciar
 	- zero > 10T: posible "Señal Presente". Esperar positivo
 	- si llega positivo, verificar si alcanza 4T: si no, volver a 1
 	- one > 4T: posible START
 	- esperar 8T y leer bit
 	- repetir paso anterior por 
 	
 */
void RxReceiver_update(RxReceiver *me)
{
	//MAIN RX STATE MACHINE
	
	switch (me->_st) {
		case IDLE:
			break;
			
		case WAITING_SILENCE:  // Esperar 0 estable por t > 2400us
			if ((PORTA & me->_rxPinMask) != 0x00) {  // "1" cancela cuenta, seguir esperando
				me->_t = 0;
				break;	
			}		
			
			if (++me->_t > 10) {  // incrementar t hasta tMin y pasar a START	
				me->_st = WAITING_START;	
			}		
			break;
			
		case WAITING_START: // Esperar 1
			if ((PORTA & me->_rxPinMask) == 0x00) {  // esperar "1" indefinidamente
				break;	
			}		
			
			me->_t = 0;
			me->_st = VERIFYING_START;	
			break;
			
		case VERIFYING_START:  // Debe mantenerse en 1 por 720us
			if ((PORTA & me->_rxPinMask) == 0x00) {  
				me->_t = 0;
				me->_st = WAITING_SILENCE;  // ERROR
				break;
			}	
			
			if (++me->_t >= 5) {	// superado el mínimo, START detectado.
				// Lanzar evento!
				if (null != me->_onStartDetected) {
					me->_t = 0;
					me->_st = IDLE;   // DEBUG ONLY
					me->_onStartDetected();	
				}				
			}
				
			break;  // seguir esperando start
			
		case WAITING_RETZERO:
			break;
			
		case WAITING_BIT:
			break;
			
		case DECODING_BIT:
			break;
	
	}		
}//
			




/***************************************
 *                                     * 
 *         S I N G L E T O N           *
 *                                     *
 ***************************************/

RxReceiver theRx;

//	

