//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 50    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 20/08/13 7:58                                  $
//|        $Archive:: /@C18/@STARTERS/CTimers/Application.c          $
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
	
	Genera 10 pulsos (eventos) onTimeElapsed separados cada 1 segundo.
	Al concluir los 10 pulsos, genera onTicksDone y relanza el timer.
	Muestra por UART 232 los eventos:
	
		onTimeElapsed(1)
		onTimeElapsed(2)
		onTimeElapsed(3)
		...
		onTimeElapsed(10)
		---- onTicksDone() ----
		
		onTimeElapsed(1)
		onTimeElapsed(2)
		onTimeElapsed(3)
		...
		onTimeElapsed(10)
		---- onTicksDone() ----
		
		onTimeElapsed(1)
		onTimeElapsed(2)
		...
	
	
	============================================================================
	
	Estructura:
	-Includes
		--Macros
		--Standard Libraries
		--User Definitions (device, fuses, typedefs, sfrs)
		--Child Classes headers
		--Self Header
		--ISR Header
		--IO port pins defines
		
	-Public App Object variable (declarada extern en Application.h)
	-Declaraciones de cada Event Handler de cada Child Object
	-Interruption Vectors
	
	-main()
		--InitSFR()
		--App_ctor(&app)
		--Loop:
			---App_run(&app)
			
	-App constructor definition
	-Definiciones de los methods de la App
	-Definiciones para cada Event Handler de cada Child Object
	
	Archivos externos (Project Settings)
		- dir_inc=C:\MCC18\h
		- dir_lib=C:\MCC18\lib	
		
	Visual Source Safe info:
		- database = E:\VSS\srcsafe.ini
		- project location = $/@C18/@STARTERS/CTimers
		
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
#include "Timer.h"

/* SELF HEADER */
#include "application.h" // definición del objeto Aplicacion
#include "isr.h"
#include "io_cfg.h"

/* OBJETO APLICACION */						
#pragma udata APPDATA
Application app;
#pragma udata

/* H A N D L E R S */  

// para Timers
void tmr0_onTimeElapsed(void*);
void tmr0_onTicksDone(void*);

// M E T H O D S
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
	InitSFR();
	printf((frchar*)"\r\n\r\n---RESET: test Timers APP ---\r\n");
	// ASSERT(TRUE == FALSE);   // test ASSERT utility
	
	App_ctor(&app);   //Construye todos los objetos hijos

	INTCON |= GIE_ON;
	
	while (TRUE) {
		ClrWdt();
		App_run(&app);
	}
}//


/*==========================================================================*/

/***************************************
 *                                     * 
 *       C O N S T R U C T O R         *
 *                                     *
 ***************************************/
void App_ctor(Application *me) {
	
    /***************************************
     *                                     *
     *     		B U T T O N S              *
     *                                     *
     ***************************************/
    Timer_ctor(&me->_tmr0, 	// objeto a construir
        (void*)me,			// parent
        100,				// periodo del pulso : 1000ms
        10,					// Cantidad de pulsos: 10
        tmr0_onTimeElapsed,	// Evento en cada flanco descendente de pulso
        tmr0_onTicksDone);	// Evento al completar los 10 pulsos
							
 	Timer_start(&me->_tmr0);
 	
	me->_state = RUNNING;  		// estado inicial
	me->_cnt = 0;				// cantidad de pulsos emitidos dentro cada tren de pulsos
	PORTD = 0x00;				// apagar todos los leds
	app_handled();				// default message: NONEWS

}//


void App_run(Application *me)
{
    uint8_t     i = 0;
	
    /* THREAD 0 */
    switch(me->_state)
    {
        case PAUSED:
            break;

        case RUNNING: {
            switch (app_getMsg())
            {
                case TIME_ELAPSED:
                	LED0 = ~LED0;
                	printf((frchar*)"\r\nonTimeElapsed(%d)", me->_cnt);
                    app_handled();
                    break; 	// return a main()
                    
                case TICKS_DONE:
                	LED1 = ~LED1;
                	printf((frchar*)"\r\n---- onTicksDone() ----\r\n");              	
                	Timer_start(&me->_tmr0);  // Relanzar Timer
                    app_handled();
                    break; 	// return a main()
                    
                 default:
                    break; 	// return a main()

            } // end switch 2
        } // end case
    } // end switch 1
} // end function


/****************************************************************************
 *                                                                          * 
 *                    E V E N T   H A N D L E R S                           *
 *                                                                          *
 ****************************************************************************

/***************************************
 *                                     * 
 *     T I M E R S        E. H.        *
 *                                     *
 ***************************************/
void tmr0_onTimeElapsed(void *ap) {
	Application *a = (Application *)ap;
	++a->_cnt;
    a->_msg = TIME_ELAPSED;
}//


void tmr0_onTicksDone(void *ap) {
	Application *a = (Application *)ap;
    a->_cnt = 0;
    app._msg = TICKS_DONE;
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
