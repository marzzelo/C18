//;+------------------------------------------------------------------+
//;|       $Workfile:: isr.c                      $ $Revision:: 51    $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 30/08/13 8:25                                  $
//;|        $Archive:: /@C18/@STARTERS/CButton/isr.c                  $
//;+------------------------------------------------------------------+
#include <p18cxxx.h>
#include <string.h>					 
#include <stdio.h>	

#include "typedefs.h"
#include "ifcondic.h"   							   

#include "io_cfg.h"    
#include "CButton.h"
#include "SPI.h"

#include "Application.h"
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
	
	
	//+-------------+
	//| T I M E R 1 |
	//+-------------+
	if(PIR1bits.TMR1IF)	{
		PIR1bits.TMR1IF = 0;		
		TMR1H = 0xFC;		
		TMR1L += 0X18;
		/////////////////////////////
		//  100 us TASKS           //
		/////////////////////////////
		
	} 

}
//



/*################################################
 #                                               #
 #                     1 ms                      #
 #                                               #
 ################################################*/
void Tasks1ms() {

}//




/*################################################
 #                                               #
 #                   10 ms                       #
 #                                               #
 ################################################*/
void Tasks10ms() {

	if (RCSTA & 0b00000110) {
		RCSTAbits.CREN = 0;
		RCSTAbits.CREN = 1;
		PIE1bits.RCIE = 1;
	}	
	
	// CHECK BUTTONS
	CButton_update(&app._sw1); 
	CButton_update(&app._sw2); 
}//



/*################################################
 #                                               #
 #                   100 ms                      #
 #                                               #
 ################################################*/
void Tasks100ms(void) {

		
}//



/*################################################
 #                                               #
 #                   1 seg                       #
 #                                               #
 ################################################*/
void Tasks1seg() {

}//
