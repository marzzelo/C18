//+------------------------------------------------------------------+
//|       $Workfile:: Application.h              $ $Revision:: 28    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 21/08/13 15:19                                 $
//|        $Archive:: /@C18/@STARTERS/CUartIO/Application.h          $
//+------------------------------------------------------------------+
//! \file Application.h
//! \brief Background Processes

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Cplus.h"
						           	
typedef enum AppState_ {
	PAUSED,
	RUNNING
	
} AppState;

typedef enum AppMessage_ {
	NONEWS,
	STR_RECEIVED,
	WBF,
} AppMessage;


/***************************************
 *                                     *
 *  C L A S S   A P P L I C A T I O N  *
 *                                     *
 ***************************************/
CLASS(Application)	
	AppState _state;
	AppMessage _msg;
	
METHODS
	/* C O N S T R U C T O R */
	void App_ctor(Application *me);
	
	/* E V E N T S */
	
END_CLASS

/***************************************
 *                                     *
 *      S I N G L E T O N   A P P      *
 *                                     *
 ***************************************/
extern Application app;

#define app_getMsg() 		CBuff_pop(&appBuffer, &me->_msg)
#define app_sendMsg(msg) 	CBuff_push(&appBuffer, (msg))

#endif	
//
