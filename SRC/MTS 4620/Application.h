//+------------------------------------------------------------------+
//|       $Workfile:: Application.h              $ $Revision:: 18    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 16/03/12 2:45p                                 $
//|        $Archive:: /@C18/SRC/Explorer1/Application.h              $
//+------------------------------------------------------------------+
//! \file Application.h
//! \brief Background Processes

#ifndef _APPLICATION_H
#define _APPLICATION_H

						           	
typedef enum AppState_ {
	SENDING_START,
	CHECKING_SWITCHES,
} AppState;

typedef enum AppMessage_ {
	NONEWS,
	SW1_CLICK,
	SW2_CLICK,
	LCD_READY,
	INCOMMING_MSG,
} AppMessage;


CLASS(Application)	
	CButton _sw1;
	CButton _sw2;
	SPI _SPI1;	// MCP 23S17
	CLeds _leds;
	AppState _state;
	AppMessage _msg;
	
METHODS
	void App_ctor(Application *me);
	void App_sendMsg(Application *me, uint8_t msg);
	AppMessage App_getMsg(Application *me);
	void App_handled(Application *me);
	void App_onNSweeps(void*);
	
END_CLASS

extern Application app;
extern DAQ daq;

#define App_sendMsg(me, msg) 		(me)->_msg = (msg)
#define App_getMsg(me) 				(me)->_msg
#define App_handled(me) 			(me)->_msg = NONEWS

#define app_sendMsg(msg)	App_sendMsg(&app, (msg))
#define app_getMsg()		App_getMsg(&app)
#define app_handled()		App_handled(&app)



#endif	
//
