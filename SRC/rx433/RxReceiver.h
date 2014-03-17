//+--------------------------------------------------------------------------+
//|  $Workfile:: UartReader.h                          $ $Revision:: 14      $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 13/01/12 9:29a                                               $
//|  $Archive:: /@C18/SRC/MTS/UartReader.h                                   $
//+--------------------------------------------------------------------------+
/*! @file RxReceiver.h
 */

#ifndef RXRECEIVER_H_
#define RXRECEIVER_H_

#include "typedefs.h"


/*************************************************************************//** 
 * Decodificador de recepci�n RF 433.
 *  \author    Marcelo A. Vald�z
 *  \copyright FAdeA - C�rdoba
 *  \note Todos los campos deben considerarse PRIVATE. S�lo deben accederse 
 *        mediante el constructor y metodos accesors.
 ****************************************************************************/
CLASS(RxReceiver)		
	WORD3 _data;
	port_t *_rxPort;
	uint8_t _rxPinMask;
	uint8_t _lastButton;
	uint16_t _t;
	uint16_t _tMax;
	uint16_t _tMin;	
	uint8_t _st;
	EventHandler _onStartDetected;
	EventHandler _onButtonPressed;

METHODS

/*************************************************************************//** 
 * Constructor del RxReceiver.
 * @param[in]   rxPort	Puerto de IO de Rx data
 * @param[in]   rxPinMask	mascara del pin de Rx data
 * @param[in]   onStartDetected	EventHandler, se ha detectado bit de start
 * @param[in]   onButtonPressed EventHandler, se ha decodificado completamente la se�al
 *
 * @code EJEMPLO:
 				theRx_ctor(&PORTA, 0x80, onRFStart, onRFButton);
   				theRx_start();  
 * @endcode
 * @related	    RxReceiver
 ****************************************************************************/
	void RxReceiver_ctor( 	RxReceiver *me,
							port_t *rxPort,  
							uint8_t rxPinMask,
							EventHandler onStartDetected,
							EventHandler onButtonPressed);
	
/*************************************************************************//** 
 * Iniciar la espera del tren de pulsos de RF
 * @param[in]    me			This
 * @related	    RxReceiver
 ****************************************************************************/
	void RxReceiver_start(RxReceiver *me);
	
/*************************************************************************//** 
 * Detener la espera de tren de pulsos de RF
 * @param[in]    me			This
 * @related	    RxReceiver
 ****************************************************************************/
	void RxReceiver_stop(RxReceiver *me);

/*************************************************************************//** 
 * Limpiar el buffer. Rellenarlo con 0x00
 * @param[in]    me			This
 * @related	    RxReceiver
 ****************************************************************************/
	void RxReceiver_clearBuff(RxReceiver *me);
	
/*************************************************************************//** 
 * Actualizar la m�quina de estados de recepci�n de Rx-433
 * @param[in]    me			This
 * @related	    RxReceiver
 ****************************************************************************/
	void RxReceiver_update(RxReceiver *me);
	

END_CLASS

// SINGLETON
extern 	RxReceiver theRx;

/****************************************************************************
 *  Las siguientes macros utilizan el singleton theRx como par�metro de     *
 *  los m�todos de la clase RxReceiver                                      *
 ****************************************************************************/
#define theRx_ctor(rxPort, rxPinMask, onStartDetected, onButtonPressed) \
							RxReceiver_ctor(&theRx, rxPort, rxPinMask, onStartDetected, onButtonPressed);
#define theRx_start()		RxReceiver_start(&theRx)
#define theRx_stop()		RxReceiver_stop(&theRx)
#define theRx_clearBuff()	RxReceiver_clearBuff(&theRx)
#define theRx_update()		RxReceiver_update(&theRx)

#endif
