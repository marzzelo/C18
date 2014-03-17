//+--------------------------------------------------------------------------+
//|  $Workfile:: CButton.h                         $ $Revision:: 6           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 29/02/12 2:05p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/CButton.h                                $  
//+--------------------------------------------------------------------------+
//! \file CButton.h
//! ### Control individual de Tact Switchs SPST.


/* C O D I G O   C O M E N T A D O   P A R A    M O D E L O  */


#ifndef CBUTTON_H_
#define CBUTTON_H_

#define IS_PRESSED !btnState			///< usar !btnState para logica NEGATIVA
#define LONGPRESS_TIME	100								///< en unidades de 10ms


#include "typedefs.h"

typedef enum _States {
	BTN_RELEASED,
	BTN_PRESSED,
	BTN_WAITRELEASE
} States;

/*************************************************************************//** 
 * ## Control individual de Tact Switchs SPST
 * @author      Marcelo A. Vald�z
 * @copyright   FAdeA - C�rdoba
 ****************************************************************************/
CLASS(CButton)
    port_t* _port;
    uint8_t _pin;
    BOOL _enabled;		
    BOOL _sampleC, _sampleB, _lastDebounceResult;
    EventHandler _onPress;
    EventHandler _onRelease;
    EventHandler _onLongPress;
    EventHandler _onLongRelease;	
    uint8_t _longPressCounter;
    uint8_t _fsmState;

METHODS
/*************************************************************************//** 
 * Constructor de la Clase.
 * @author      Marcelo A. Vald�z
 * @copyright   FAdeA - C�rdoba
 * @param[in] 	port	Puntero al puerto donde est� ubicado el bot�n
 * @param[in] 	pin		Pin del puerto donde est� conectado el bot�n
 * @param[in] 	onPress	Handler para bot�n presionado (con debounce)
 * @param[in] 	onRelease Handler para bot�n soltado (con debounce)
 * @param[in] 	onLongPress Handler para bot�n presionado luego de LONGPRESS_TIME
 *							decenas de [ms].
 * @param[in] 	onLongRelease Handler para bot�n soltado luego de un LongPress
 * @code        CButton_ctor(&me->_sw1, &PORTB, 0, 
 *							onSw1Press, 
 *							onSw1Release, 
 *							onSw1LongPress, 
 *							onSw1LongRelease);    @endcode
 * @related     CButton
 ****************************************************************************/
    CButton *CButton_ctor(CButton *me, 
	port_t* port, 
	uint8_t pin,
	EventHandler onPress, 
	EventHandler onRelease,
	EventHandler onLongPress,
	EventHandler onLongRelease);
	
/*************************************************************************//** 
 * Activa o desactiva totalmente el chequeo del bot�n. No se genera ning�n
 *	evento relacionado al bot�n.
 * @param[in] 	enable		Activa o desactiva el bot�n
 * @code        CButton_enable(&myButton, FALSE)    @endcode
 * @related     CButton
 ****************************************************************************/
	void CButton_enable(CButton *me, BOOL enable);
	
/*************************************************************************//** 
 * Chequea bot�n y genera eventos onPress, onRelease, etc.
 * Debe ubicarse en ISR para ser llamada cada 10ms
 * @code        CButton_update(&myButton)    @endcode
 * @related     CButton
 ****************************************************************************/
	void CButton_update(CButton *me);	
END_CLASS

#endif
