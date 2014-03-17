//+--------------------------------------------------------------------------+
//|  $Workfile:: CButton.c                         $ $Revision:: 5           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 29/02/12 12:17p                                              $
//|  $Archive:: /@C18/SRC/Explorer1/CButton.c                                $
//+--------------------------------------------------------------------------+

/* C O D I G O   C O M E N T A D O   P A R A    M O D E L O  */


#include "qassert.h"
#include "CButton.h"

DEFINE_THIS_FILE;

/* La siguiente función (auxiliar) se declara static con el fin principal de documentarla
como PRIVATE. El efecto en C es permitir reutilizar el nombre en otro módulo sin producir
conflictos ya que esta definición sólo será visible localmente */
static BOOL CButton_debounce(CButton *me); 


/* El Constructor permite asignar valores a las propiedades y métodos declarados en CLASS 
(ver CButton.h) para no tener que accederlos directamente (encapsulamiento).

Los campos de la clase se nombran comenzando con _ (guión bajo) para documentarlos como PRIVATE.
De la misma forma, los manejadores de evento se denominan comenzando con _on.

El tipo EventHandler ha sido definido en typedefs.h como  "typedef void (*EventHandler)(void)"
es decir, un puntero a función que toma un parametro void y devuelve void. Estos manejadores
de evento simplemente deben definirse en main() y serán llamados automáticamente desde _update()
que se ejecuta periódicamente en ISR(). _update() genera las llamadas a TODOS los manejadores y no
es necesario generar la llamada manualmente.

Los EventHandlers son PROPIEDADES (punteros a función) y no métodos.
Los métodos, en cambio, se declaran en la sección METHODS de la CLASS (ver CButton.h) */
CButton *CButton_ctor(CButton *me, 
	port_t* port, 
	uint8_t pin,
	EventHandler onPress, 
	EventHandler onRelease,
	EventHandler onLongPress,
	EventHandler onLongRelease)
{
	me->_port = port;
	me->_pin = pin;
	me->_enabled = TRUE;
	
	me->_onPress = onPress;
	me->_onRelease = onRelease;
	me->_onLongPress = onLongPress;
	me->_onLongRelease = onLongRelease;
	
	me->_sampleC = me->_sampleB = me->_lastDebounceResult = TRUE; 
	me->_longPressCounter = 0;  // temporizador
	me->_fsmState = BTN_RELEASED;
		
	return me;
} //

/* Las definiciones de métodos se realizan aquí. Las definiciones de los
EventHandlers debe realizarlos el usuario de la clase, en main() */
void CButton_enable(CButton *me, BOOL enable) {
	me->_enabled = enable;
}

/* Los métodos que realizan polling en ISR se nombran terminando con _update(<clase> *me)
   y desde ellos se generan las llamadas a los correspondientes EventHandlers */
void CButton_update(CButton *me)
{
	BOOL btnState;
	
	if (!me->_enabled) return; // No se realiza ningún Callback si el botón está deshabilitado

	btnState = CButton_debounce(me); // en CButton.h: #define IS_PRESSED !btnState
		
	switch (me->_fsmState) 
	{
		case BTN_RELEASED:
			if (IS_PRESSED) {	// en CButton.h: #define IS_PRESSED !btnState
				me->_fsmState = BTN_PRESSED;
				if (me->_onPress != null) me->_onPress(); 				// ---> Callback!
			}
			break;
		
			
		case BTN_PRESSED:
			if (IS_PRESSED) {
				if (me->_longPressCounter++ > LONGPRESS_TIME) {
					me->_longPressCounter = 0;
					me->_fsmState = BTN_WAITRELEASE;
					if (me->_onLongPress != null) me->_onLongPress();  	// ---> Callback!
					return;
				} 
			} 	
			else {	// IS RELEASED
				me->_longPressCounter = 0;
				me->_fsmState = BTN_RELEASED;
				if (me->_onRelease != null) me->_onRelease();  			// ---> Callback!
			}
			
			break;
			
		
		case BTN_WAITRELEASE:
			if (!IS_PRESSED) {
				if (me->_onLongRelease != null) me->_onLongRelease(); 	// ---> Callback!
				me->_fsmState = BTN_RELEASED;
			}
			break;
	}
			
}//


// Función Auxiliar, (static = PRIVATE)
static BOOL CButton_debounce(CButton *me)
{
	BOOL sampleA = *(me->_port) & (1<<me->_pin);
	
	me->_lastDebounceResult = 
		me->_lastDebounceResult & (sampleA | me->_sampleB | me->_sampleC) | 
			(sampleA & me->_sampleB & me->_sampleC);
			
	me->_sampleC = me->_sampleB;
	me->_sampleB = sampleA;
	return me->_lastDebounceResult;
}//

