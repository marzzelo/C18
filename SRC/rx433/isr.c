//;+------------------------------------------------------------------+
//;|       $Workfile:: isr.c                      $ $Revision:: 68    $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 23/12/13 14:57                                 $
//;|        $Archive:: /@C18/SRC/rx433/isr.c                          $
//;+------------------------------------------------------------------+
#include <p18cxxx.h>
#include <string.h>					 
#include <stdio.h>	

#include "typedefs.h"
#include "ifcondic.h"   							   

#include "io_cfg.h"    

#include "Application.h"
#include "UartReader.h"
#include "Relay.h"
#include "Daq.h"
#include "xusart.h"
#include "rxreceiver.h"

#include "isr.h"


// Contadores 
volatile byte 	TMRx10ms;	
volatile byte  	TMRx100ms;	
volatile byte  	TMRx1s;			
volatile byte	TMRx1min;				
volatile byte	TMRx1h;					
volatile byte	TMRx1d;	

// Tareas
static void Tasks1ms(void);
static void Tasks10ms(void);
static void Tasks100ms(void);
static void Tasks1seg(void);

#pragma interrupt ISRH
void ISRH()	{
	LATD |= 0b00000010;
	
	//+-------------+
	//| T I M E R 1 |
	//+-------------+
	if(PIR1bits.TMR1IF)	{
		
		PIR1bits.TMR1IF = 0;		
		
		/////////////////////////////
		//   10 us TASKS           //
		/////////////////////////////
		
		
		//RxReceiver_update(&theRx);
		
		TMR1H = 0xFF;		
		TMR1L += 0x0F; 
	} 
	
	LATD &= 0b11111101;
}//	
 
#pragma interrupt ISRL
void ISRL()	{	
	
	
	//+-------------+
	//| T I M E R 0 |
	//+-------------+
	
	/*********************************************************************
 	 *       NOTA: VALORES CALCULADOS PARA OSCILADOR INTERNO DE 8MHz
 	 *********************************************************************/
 	if (INTCONbits.T0IF) {								
		INTCONbits.T0IF = 0;
		TMR0L += 6; // TMR0 recarga cada 1ms
		Tasks1ms();
		if (!--TMRx10ms) 	{TMRx10ms = 	10;Tasks10ms();
		if (!--TMRx100ms) 	{TMRx100ms = 	10;Tasks100ms();
		if (!--TMRx1s) 		{TMRx1s = 		10;Tasks1seg();
		if (!--TMRx1min) 	{TMRx1min = 	60;//Tasks1min();
		if (!--TMRx1h) 		{TMRx1h = 		60;//Tasks1h();	
		if (!--TMRx1d) 		{TMRx1d = 		24;//Tasks1d();
	}}}}}}} 
	
	
	
	
	//+-----------------------------+
	//| U A R T   I N T E R R U P T |
	//+-----------------------------+
	if (PIR1bits.RCIF) {
		theUartReader_push(RCREG);
	} 
}
//



/*################################################
 #                                               #
 #                     1 ms                      #
 #                                               #
 ################################################*/
void Tasks1ms() {
	LATD ^= 0b00000001;
}//




/*################################################
 #                                               #
 #                   10 ms                       #
 #                                               #
 ################################################*/
void Tasks10ms() {
	uint8_t i;

	// Reset UART errors
	if (RCSTA & 0b00000110) {
		RCSTAbits.CREN = 0;
		RCSTAbits.CREN = 1;
		PIE1bits.RCIE = 1;
	}	
	
	// Update UART Reader
	theUartReader_update();
	
	// Update Buttons
	CButton_update(&app._sw1); 
	//CButton_update(&app._sw2); 
	//CButton_update(&app._sw3); 

	// Update Relays 				<--- INHABILITADO EN ADAQUS PARA NO INTERFERIR CON DAQ
//	for (i=0; i<8; i++) {
//		Relay_update(&relay[i]);
//	}
	
}//



/*################################################
 #                                               #
 #                   100 ms                      #
 #                                               #
 ################################################*/
void Tasks100ms(void) {
//	if (LATE > 0)  <-- hace blinkear los leds en PORTE
//		LATE = 0x00;
//	else
//		LATE = XPORTE;
}//



/*################################################
 #                                               #
 #                   1 seg                       #
 #                                               #
 ################################################*/
void Tasks1seg() {

}//
