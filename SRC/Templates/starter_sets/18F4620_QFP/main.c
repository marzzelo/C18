//+------------------------------------------------------------------+
//|       $Workfile:: main.c                     $ $Revision:: 5     $
//+------------------------------------------------------------------+
//|         $Author:: Mav                                            $
//|        $Modtime:: 25/06/11 3:31p                                 $
//|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/main $
//+------------------------------------------------------------------+

/****************************************************************************
 *                                                                          * 
 *                      B  A  C  K  G  R  O  U  N  D                        *
 *                                                                          *
 ****************************************************************************/

#include "ifcondic.h"
#include "qassert.h"		// LINKEAR CON QASSERT.C

#include <p18cxxx.h>					
#include <string.h>			
#include <stdlib.h>					
#include <stdio.h>		
				
#include "p18fxxx_defs.h" 
#include "typedefs.h"   

#include "eeprom.h"			// BIBLIOTECAS PROPIAS
#include "flash.h"						
#include "xusart.h"                  	
#include "xadc.h"						
#include "ledex.h"						
#include "xstrings.h"					
#include "bitops.h"
#include "bgwriter.h"	 	// Background Writer

#include "fsm.h"
#include "isr.h"						
#include "io_cfg.h"			// PUERTOS
#include "fuses.h"			// FUSES	
#include "init_pic.h"		// SFR	
#include "romdata.h"
#include "flags.h"
	
#include "delayer.h"
#include "bgwriter.h"
#include "fgreader.h"

#include "main.h"						

DEFINE_THIS_FILE;

/***************************************
 *                                     * 
 *         VARIABLES PRIVADAS          *
 *                                     *
 ***************************************/
 
static uint8_t index = 0;

// OBJETO: Fsm de llamadas tras delays *
Fsm myFsm;	
	uint16_t tmr[] = {1000, 1000, 1000};
	static void f0(void);
	static void f1(void);
	static void f2(void);
	EventHandler ev[] = {f0, f1, f2};

	
// OBJETO: Delay con llamada a funcion al final
Delayer myDelay;	
	
// OBJETO: Writer. Requiere reservar un buffer en main()
Writer writer1;
	static char uartBuff[30] = {0};
	
// OBJETO: Reader. Requiere reservar un buffer en main()	
Reader reader1;
	static char rxBuff[128]	= {0};
	static void onDatasetReady(ReaderRc);
	char eols[]		= "\n\r"; 
	

// VARIABLES EN FLASH ROM	
#pragma romdata
frchar delims[] 	= " \"\n\r,;=";


/***************************************
 *                                     * 
 *         FUNCIONES PRIVADAS          *
 *                                     *
 ***************************************/
// static ...




// Vector de interrupciones de ALTA PRIORIDAD       
#pragma code ISRH_CODE = 0x8		
void high_vector() {_asm goto ISRH _endasm	}

//#pragma code ISRL_CODE = 0x18
//void low_vector() {_asm goto ISRL _endasm}


/***************************************
 *                                     * 
 *          m a i n  ( )               *
 *                                     *
 ***************************************/
#pragma code
void main()	
{   
	/***************************************
	 *                                     * 
	 *   i n i c i a l i z a c i o n e s   *
	 *                                     *
	 ***************************************/
	InitSFR();
		
	#define N_ESTADOS  3
	#define FSM_REP 10
	
	#define DELAY_MS 5000
	#define DELAY_REP 1
	
	//Fsm_ctor(&myFsm, N_ESTADOS, tmr, ev);
	//Fsm_start(&myFsm, FSM_REP);
	
	//Delayer_ctor(&myDelay, DELAY_MS, f0); // delay 1000ms, luego call f0()
	//Delayer_start(&myDelay, DELAY_REP); // comenzar delay en foreground
	
	Writer_ctor(&writer1, uartBuff);
	Reader_ctor(	&reader1, 
					rxBuff, 
					eols,
					DIM(rxBuff), 
					2000,
					onDatasetReady);
					
	Reader_start(&reader1);
	
	
	while (TRUE)
	{
	   /***************************************
		*                                     * 
		*       M A I N    L O O P            *
		*                                     *
		***************************************/
	
		Writer_update(&writer1);  	
		ClrWdt();
		
	}
}//


/***************************************
 *                                     * 
 *    E V E N T   H A N D L E R S      *
 *                                     *
 ***************************************/
/* NOTA: EventHandlers se ejecutan dentro de ISR. No admiten delays ni llamadas
   a funciones no reentrantes */

static void f0(void) { 
	
}


static void f1(void) {
	
}


static void f2(void) {

}


void onDatasetReady(ReaderRc rc)
{
	// debe hacerse como FSM, implementar WriterReady y ReaderReady
	// No ordenar lectura ni escritura si todavía no estan listos.
	char str[30] = {0};

	sprintf(str, (frchar*)"\r\nLEIDO: %s RC=%d\r\n", reader1.rxBuff, rc);
	Writer_write(&writer1, str);
	while(!writer1.ready);

	Reader_start(&reader1);
	
}
