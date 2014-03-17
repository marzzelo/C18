//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 51    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 16/08/13 14:49                                 $
//|        $Archive:: /@C18/@STARTERS/CLeds/Application.c            $
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
	
	Genera una secuencia de valores para el puerto de LEDS y presenta los eventos
	por UART RS232. Al finalizar la secuencia de 16 ciclos muestra el evento onLedsDone()
	y lanza nuevamente la secuencia.
	
			leds_sequence(1) -> 1
			leds_sequence(2) -> 2
			...
			leds_sequence(15) -> 15
			leds_sequence(16) -> 16
			---- onLedsDone() ----
			
			leds_sequence(1) -> 1
			leds_sequence(2) -> 2
			...
			leds_sequence(15) -> 15
			leds_sequence(16) -> 16
			---- onLedsDone() ----
			
			leds_sequence(1) -> 1
			leds_sequence(2) -> 2
				
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
		- project location = $/@C18/@STARTERS/CLeds
		
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
#include "CLeds.h"

/* SELF HEADER */
#include "application.h" // definición del objeto Aplicacion
#include "isr.h"
#include "io_cfg.h"

/* OBJETO APLICACION */						
#pragma udata APPDATA
Application app;
uint8_t seqArray[] = {0x81, 0x42, 0x24, 0x18, 0x24, 0x42, 0x81, 0x42, 0x24, 0x18, 0x24, 0x42};

#pragma udata

/* H A N D L E R S */  

// para CLeds
uint8_t leds_sequence(void);  		// Modo Secuencial: Función secuencia
uint8_t leds_onLedsDone(void);		// Modo Secuencial: Al finalizar n ciclos
void leds_onArrayCycle(void);		// Modo Array: Al reciclar array


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
	printf((frchar*)"\r\n\r\n---RESET: test CLeds APP ---\r\n");
	// ASSERT(TRUE == FALSE);   // test ASSERT utility
	
	App_ctor(&app);   //Construye todos los objetos hijos

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
    CLeds_ctor(&me->_leds, 	// objeto a construir
        &PORTD,
        20,
        32,
        leds_sequence,
        leds_onLedsDone);	
        
    CLeds_arrayModeSetup(&me->_leds,
    	seqArray,
    	DIM(seqArray),
    	leds_onArrayCycle);
							
 	CLeds_startSeq(&me->_leds);
 	
	me->_state = RUNNING;  		// estado inicial
	me->_cnt = 0;				// cantidad de pulsos emitidos dentro cada tren de pulsos
	me->_ledValue = 0;			// valor inicial de la función de secuencias
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
                	printf((frchar*)"\r\nleds_sequence(%d) -> %d", me->_cnt, me->_ledValue);
                    app_handled();
                    break; 	// return a main()
                    
                case TICKS_DONE:
                	printf((frchar*)"\r\n---- onLedsDone() ----\r\n");              	
                	CLeds_startArray(&me->_leds);  // Relanzar leds en modo ARRAY
                    app_handled();
                    break; 	// return a main()
                    
                 case ARRAY_CYCLED:
                 	printf((frchar*)"\r\n---- onArrayCycle() ----\r\n");              	
                	CLeds_startSeq(&me->_leds);  // Relanzar leds en modo CALCULADO
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
uint8_t leds_sequence() {
	++app._cnt;
    app._msg = TIME_ELAPSED;
    return ++app._ledValue;
}//


uint8_t leds_onLedsDone() {
    app._cnt = 0;
    app._ledValue = 0;
    app._msg = TICKS_DONE;
    return 0xAA;
}//

void leds_onArrayCycle() {
	app._msg = ARRAY_CYCLED;
}

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
