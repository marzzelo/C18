//+------------------------------------------------------------------+
//|       $Workfile:: Application.h              $ $Revision:: 20    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 12/04/12 12:12p                                $
//|        $Archive:: /@C18/SRC/Explorer1/Application.h              $
//+------------------------------------------------------------------+
//! \file Application.h
//! \brief Background Processes

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Cplus.h"
						           	
typedef enum AppState_ {
	PAUSED,
	RUNNING,
} AppState;

typedef enum AppMessage_ {
	NONEWS,
	SW1_PRESS,
	SW1_RELEASE,
	SW1_LONGPRESS,
	SW1_LONGRELEASE,

	SW2_PRESS,
	SW2_RELEASE,
	SW2_LONGPRESS,
	SW2_LONGRELEASE,
} AppMessage;


/***************************************
 *                                     *
 *  C L A S S   A P P L I C A T I O N  *
 *                                     *
 ***************************************/
CLASS(Application)	
	CButton _sw1; 	// Child Object
	CButton _sw2;	// Child Object

	AppState _state;
	AppMessage _msg;
	
METHODS
	/* C O N S T R U C T O R */
	void App_ctor(Application *me);
	
	void App_sendMsg(Application *me, uint8_t msg); // Macro
	AppMessage App_getMsg(Application *me);			// Macro
	void App_handled(Application *me);				// Macro
	
	/* E V E N T S */
	void App_onNSweeps(void*);						// Event
	
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
