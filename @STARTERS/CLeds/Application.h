//+------------------------------------------------------------------+
//|       $Workfile:: Application.h              $ $Revision:: 27    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 16/08/13 14:40                                 $
//|        $Archive:: /@C18/@STARTERS/CLeds/Application.h            $
//+------------------------------------------------------------------+
//! \file Application.h
//! \brief Background Processes

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Cplus.h"
#include "CLeds.h"
						           	
typedef enum AppState_ {
	PAUSED,
	RUNNING,
} AppState;

typedef enum AppMessage_ {
	NONEWS,
	TIME_ELAPSED,
	TICKS_DONE,
	ARRAY_CYCLED
} AppMessage;


/***************************************
 *                                     *
 *  C L A S S   A P P L I C A T I O N  *
 *                                     *
 ***************************************/
CLASS(Application)	
	CLeds _leds; 	// Child Object

	AppState _state;
	AppMessage _msg;
	uint8_t _ledValue;
	uint8_t _cnt;
	
METHODS
	/* C O N S T R U C T O R */
	void App_ctor(Application *me);
	
	//void App_sendMsg(Application *me, uint8_t msg); // Macro
	//AppMessage App_getMsg(Application *me);			// Macro
	//void App_handled(Application *me);				// Macro
		
END_CLASS

/***************************************
 *                                     *
 *      S I N G L E T O N   A P P      *
 *                                     *
 ***************************************/
extern Application app;







// para un objeto en general
#define App_sendMsg(me, msg) 	(me)->_msg = (msg)
#define App_getMsg(me) 		(me)->_msg
#define App_handled(me) 	(me)->_msg = NONEWS


// para el objeto &app en particular
#define app_sendMsg(msg)	App_sendMsg(&app, (msg))
#define app_getMsg()		App_getMsg(&app)
#define app_handled()		App_handled(&app)



#endif	
//
