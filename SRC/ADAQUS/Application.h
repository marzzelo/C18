//+------------------------------------------------------------------+
//|       $Workfile:: Application.h              $ $Revision:: 45    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 11/12/13 14:12                                 $
//|        $Archive:: /@C18/SRC/ADAQUS/Application.h                 $
//+------------------------------------------------------------------+
//! \file Application.h
//! \brief Background Processes

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Cplus.h"
#include "Relay.h" // para definir extern Relay relay[8] 
#include "CButton.h"
#include "CBuff.h"
#include "Daq.h"


						           	
typedef enum AppState_ {
	ST_AUTO,
	ST_MANUAL
	
} AppState;

/** Application Queue Messages enum */
typedef enum AppMessage_ {
	MSG_STR_RECEIVED,			///< Se ha recibido un string por puerto serie
	MSG_WBF,
	MSG_TON,
	MSG_CYCLE_END,
	MSG_ECHO_TOGGLE,
	MSG_LIST,
	MSG_CONFIRMRESET,
	MSG_RESET,
	MSG_SAVE,
	MSG_LOAD,
	
	MSG_START,
	MSG_STOP,
	MSG_PAUSE,
	MSG_RESUME,
	
	MSG_SW1_PRESS,				///< Callback: se ha presionado Sw1
	MSG_SW1_RELEASE,			///< Callback: se ha soltado Sw1
	MSG_SW1_LONGPRESS,			///< Callback: se ha presionado (largo) Sw1
	MSG_SW1_LONGRELEASE,		///< Callback: se ha soltado (largo) Sw1
	MSG_SW2_PRESS,				///< Callback: se ha presionado Sw2
	MSG_SW2_RELEASE,			///< Callback: se ha soltado Sw2
	MSG_SW2_LONGPRESS,			///< Callback: se ha presionado (largo) Sw2
	MSG_SW2_LONGRELEASE,		///< Callback: se ha soltado (largo) Sw2
	
	MSG_SWEEP_COMPLETED,		///< Callback recibido: barrido de adquisición completo
	MSG_ACQUIRE,				///< Orden de iniciar adquisición
		
} AppMessage;

typedef struct _Flags {
	unsigned ECHO: 1;
} Flags;

#define _ECHO		_flags1.ECHO

/** OVERLAY UNION */
typedef union _DaqBuff  {
	char _buff[128];
	struct {
        uint16_t _data[64];
    };
} DaqBuff;


/** CLASS Application */
CLASS(Application)	
	CButton _sw1; 	///< Child Object
	CButton _sw2;	///< Child Object
	CButton _sw3;	///< Feedback bumper 
	
	AppState _state;
	AppMessage _msg;
	char _appbuffer[10]; 	///<  buffer lineal para el CBuff
	CBuff _appBuffer;		///< Buffer de mensajes de la APP
	uint16_t _idata;		///< message integer-16 payload
	Flags _flags1;
	
METHODS
	
END_CLASS

/** Singleton */
extern Application app;	///< Singleton declaration


/***************************************
 *                                     *
 *    c h i l d   O B J E C T S        *
 *                                     *
 ***************************************/
extern Relay relay[8];

extern uint16_t cnt; 		///< contador de ciclos para ciclado infinito

#define app_getMsg() 		CBuff_pop(&app._appBuffer, &me->_msg)
#define app_sendMsg(msg) 	CBuff_push(&app._appBuffer, (msg))



/**************************************************
 *                                                *
 *         E E P R O M    P A G E   0             *
 *                                                *
 **************************************************/	
#define EE_TON_ARRAY		0,0 		///< [16] = [2]·8 Ton
#define EE_TOFF_ARRAY		0,16		///< [16] = [2]·8 Toff
#define EE_OFFSET_ARRAY  	0,32		///< [16] = [2]·8 Offset
#define EE_CYCLES_ARRAY		0,48		///< [16] = [2]·8 Cycles
#define EE_COUNTER_ARRAY	0,64		///< [16] = [2]·8 contador de ciclos
#define	EE_RELAY_FLAGS		0,80		///< [8] = [1] * 8
#define EE_INDEX_RELAY		0,88		///< [1] master relay
#define EE_CNT				0,89		///< [2] general cycles count (uint16_t cnt)




#endif	
//
