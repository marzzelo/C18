//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 53    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 21/08/13 13:37                                 $
//|        $Archive:: /@C18/@STARTERS/CUartIO/Application.c          $
//+------------------------------------------------------------------+

/*
	Funcionamiento:
	Hardware: 	PICDEM™ PIC18 Explorer Demonstration Board
				Board-mounted PIC18F8722
				PICkit™ 3 Programmer/Debugger
				Programación: USB
				Monitor: RS-232 / DockLight
				
	Switches ubicados en RB0 y RA5.
	Leds ubicados en PORTD.
	Conectar jumper de habilitaciòn de LEDS
	Selector ICE/PIC en PIC
	Desconectar jumpers EEPROM y USB
	
	
	
	============================================================================
*/	

/* MACROS */
#define _NASSERT  /* quitar el guion para deshabilitar assertions */

#include "ifcondic.h"
#include "qassert.h"		
DEFINE_THIS_FILE; /* definido en qassert.h, para usar con ASSERT(test) etc. */

/* STANDARD LIBRARIES */
#include <p18cxxx.h>
#include <string.h>			
#include <stdlib.h>					
#include <stdio.h>	

#include "xusart.h"

/* USER DEFINITIONS */
#include "fuses_8722.h"
#include "init_pic.h"					
#include "p18fxxx_defs.h" 
#include "typedefs.h"   

/* CLASES */
#include "UartReader.h"
#include "UartWriter.h"

/* SELF HEADER */
#include "application.h" // definición del objeto Aplicacion
#include "isr.h"
#include "io_cfg.h"

/* OBJETO APLICACION */						
#pragma udata APPDATA
Application app; // extern singleton

#pragma udata BUFFDATA
char wbuffer[60] = {0x00};
char tbuffer[60] = {0x00};
char rbuffer[60] = {0x00};
char appbuffer[10];

#pragma udata
CBuff wBuffer;		// Buffer de escritura
CBuff rBuffer;		// Buffer de lectura
CBuff appBuffer;	// Buffer de mensajes de la APP

char eols[] = "\0\r\n+";

/* H A N D L E R S */  
void onStringReceived(ReaderRc rrc);
void app_onRBufferFull(void);
void app_onWBufferFull(void);


// para Application
static void App_run(Application *me);

 
/***************************************
 *                                     *
 *           V E C T O R S             *
 *                                     *
 ***************************************/
#pragma code ISRH_CODE = 0x08		
void high_vector() {_asm goto ISRH _endasm	} //
#pragma code ISRL_CODE = 0x18
void low_vector() {_asm goto ISRH _endasm	} //
#pragma code


/*==========================================================================*/
void main()	
{   
	uint8_t key;

	//INT_LOCK(key);		// Disable interruptions
	
	InitSFR();
	App_ctor(&app);   	// Construye todos los objetos hijos
	
	//INT_UNLOCK(key);	// enable interruptions

	App_run(&app);

}//


/*==========================================================================*/


void App_run(Application *me) {
    uint8_t i = 0;

	
	while (TRUE) {
		
		ClrWdt();
		
	    /******************************** THREAD 0 */
	    switch(me->_state)
	    {
	        case PAUSED:
	            break;
	
	        case RUNNING: {
		        if (app_getMsg() == BUFF_EMPTY) 
		        	break;
		        	
	            switch (me->_msg)
	            {	
	                case STR_RECEIVED:
	                	CBuff_popString(&rBuffer, tbuffer);
						CBuff_pushRomString(&wBuffer, (frchar*)"\r\nreceived a string: ");
						CBuff_pushString(&wBuffer,tbuffer);
						
						theUartReader_clearBuff();
						theUartReader_start();	// Esperar nuevo comando
						break;
						
					case WBF:
						LED1 = 1;
						printf((frchar*)"WRITE BUFFER FULL");
						break;
	            } 
	            break;
	        } 
	    }
	    
	    
		/******************************** THREAD 1 */
		theUartWriter_update();
	}
}//



/***************************************
 *                                     * 
 *       C O N S T R U C T O R         *
 *                                     *
 ***************************************/
void App_ctor(Application *me) {
	
	// Construir los CBuffer para la Uart
	CBuff_ctor(&wBuffer,
		wbuffer,
		DIM(wbuffer),
		app_onWBufferFull);
		
	CBuff_ctor(&rBuffer,
		rbuffer,
		DIM(rbuffer),
		null);
		
	// Construir CBuffer para la cola de mensajes de la app
	CBuff_ctor(&appBuffer,
		appbuffer,
		DIM(appbuffer),
		null);
		
	// Construir el controlador de escritura de la UART
	theUartWriter_ctor(
		&wBuffer, 
		null);
		
	// Iniciar la UART
	theUartWriter_start();
	
	// Construir el controlador de lectura
	#define	TIMEOUT 500L  // (5 segundos)
	theUartReader_ctor(
		&rBuffer, 
		eols, 
		DIM(eols), 
		TIMEOUT, 
		onStringReceived);
		
	theUartReader_start();	
	
	// Mensaje inicial usando theUartWriter
	CBuff_pushRomString(&wBuffer, (frchar*)"\r\n\r\n---RESET---\r\n");
 	
	me->_state = RUNNING;  		// estado inicial
}//



/****************************************************************************
 *                                                                          * 
 *                    E V E N T   H A N D L E R S                           *
 *                                                                          *
 ****************************************************************************/
void onStringReceived(ReaderRc rrc) {
	app_sendMsg(STR_RECEIVED);
	
}//

void app_onWBufferFull() {
	app_sendMsg(WBF);
}//



/***************************************
 *                                     * 
 *     o n    A S S E R T (  )         *
 *                                     *
 ***************************************/
void onAssert__(char const *file, unsigned line)
{
#ifdef __DEBUG
	printf((frchar*)"\n---- ASSERTION ERROR ----\n\tFILE:\t \"%s\" \n\t"
			  "line:\t %d", file, line);
	while(1);
#endif
}//
