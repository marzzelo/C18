//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 42    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 12/04/12 12:40p                                $
//|        $Archive:: /@C18/SRC/Explorer1/Application.c              $
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
	
	Presionando RB0 o RA5 se enciende/apaga D1 o D2  (RD0 o RD1)
	Presionando más de 1 segundo RB0 o RA5 se enciende/apaga D7 o D8  (RD6 o RD7)
	
	Al presionar o soltar ("release") cada botón, se envía un mensaje del
	evento producido a la UART, configurada en 9600 bauds 8N1
	
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
		- project location = $/@C18/@STARTERS/CButton
		
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
#include "CButton.h"

/* SELF HEADER */
#include "application.h" // definición del objeto Aplicacion
#include "isr.h"
#include "io_cfg.h"

/* OBJETO APLICACION */						
#pragma udata APPDATA
Application app;
#pragma udata

/* H A N D L E R S */  

// para CButtons
static void onSw1Press(void);
static void onSw1Release(void);
static void onSw1LongPress(void);
static void onSw1LongRelease(void);

static void onSw2Press(void);
static void onSw2Release(void);
static void onSw2LongPress(void);
static void onSw2LongRelease(void);

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
	InitSFR();
	printf((frchar*)"\r\n\r\n---RESET---\r\n");
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
    CButton_ctor(&me->_sw1,
        &PORTB, 0,
        onSw1Press,
        onSw1Release,
        onSw1LongPress,
        onSw1LongRelease);
							
    CButton_ctor(&me->_sw2,
        &PORTA, 5,
        onSw2Press,
        onSw2Release,
        onSw2LongPress,
        onSw2LongRelease);
 	
	me->_state = RUNNING;  		// estado inicial
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
                case SW1_PRESS:
                	
                	printf((frchar*)"\r\nonSw1Press()");
                    app_handled();
                    break;
                    
                case SW1_RELEASE:
                	LED0 = ~LED0;
                	printf((frchar*)"\r\nonSw1Release()");
                    app_handled();
                    break;
                    
                case SW1_LONGPRESS:
                	LED6 = ~LED6;
                	printf((frchar*)"\r\nonSw1LongPress()");
                    app_handled();
                    break;
                    
                case SW1_LONGRELEASE:
                	
                	printf((frchar*)"\r\nonSw1LongRelease()");
                    app_handled();
                    break;  
                  

                case SW2_PRESS:

                	printf((frchar*)"\r\nonSw2Press()");
                    app_handled();
                    break;
                    
                case SW2_RELEASE:
                	LED1 = ~LED1;
                	printf((frchar*)"\r\nonSw2Release()");
                    app_handled();
                    break;
                    
                case SW2_LONGPRESS:
                	LED7 = ~LED7;
                	printf((frchar*)"\r\nonSw2LongPress()");
                    app_handled();
                    break;
                    
                case SW2_LONGRELEASE:
                	
                	printf((frchar*)"\r\nonSw2LongRelease()");
                    app_handled();
                    break; 

                default:
                    break;

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
 *     C B U T T O N      E. H.        *
 *                                     *
 ***************************************/
void onSw1Press() {
    app_sendMsg(SW1_PRESS);
}
void onSw1Release() {
    app_sendMsg(SW1_RELEASE);
}
void onSw1LongPress() {
	app_sendMsg(SW1_LONGPRESS);
}
void onSw1LongRelease() {
	app_sendMsg(SW1_LONGRELEASE);
}//

void onSw2Press() {
	app_sendMsg(SW2_PRESS);
}
void onSw2Release() {
    app_sendMsg(SW2_RELEASE);
}//
void onSw2LongPress() {
	app_sendMsg(SW2_LONGPRESS);
}//
void onSw2LongRelease() {
	app_sendMsg(SW2_LONGRELEASE);
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
