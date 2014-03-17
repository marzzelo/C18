//;+------------------------------------------------------------------+
//;|       $Workfile:: isr.c                      $ $Revision:: 5     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 20/11/11 12:30a                                $
//;|        $Archive:: /@C18/SRC/Templates/starter_sets/18F4620_OOP/i $
//;+------------------------------------------------------------------+

/****************************************************************************
 *                                                                          * 
 *                      F  O  R  E  G  R  O  U  N  D                        *
 *                                                                          *
 ****************************************************************************/
#include <p18cxxx.h>
#include <string.h>					
#include <stdio.h>	

#include "typedefs.h"
#include "ifcondic.h"   	
#include "xusart.h"							   

#include "io_cfg.h"            
#include "delayer.h"
#include "bgwriter.h"
#include "fgreader.h"

#include "isr.h"



/*********************************************************************
 *               V A R I A B L E S    P U B L I C A S
 *********************************************************************/

extern Delayer 	myDelay;
extern Reader 	reader1;

 
// Contadores por software:	
volatile byte 	TMRx10ms;	
volatile byte  	TMRx100ms;	
volatile byte  	TMRx1s;			
volatile byte	TMRx1min;				
volatile byte	TMRx1h;					
volatile byte	TMRx1d;	


/*********************************************************************
 *               V A R I A B L E S    P R I V A D A S                *
 *********************************************************************/
static volatile byte i;
static volatile int tmr_aviso, tmr_beep;
// ToDo: Agregar otras variables privadas


/*********************************************************************
 *              T A R E A S     P E R I O D I C A S                  *
 *********************************************************************/
static void Tasks1ms(void);
static void Tasks10ms(void);
static void Tasks100ms(void);
static void Tasks1seg(void);

 
/*********************************************************************
 *       D E C L A R A C I O N E S    D E    F U N C I O N E S       *
 *********************************************************************/

 
#pragma interrupt ISRH
/*********************************************************************
 *       NOTA: VALORES CALCULADOS PARA OSCILADOR INTERNO DE 8MHz
 *********************************************************************/
void ISRH()			
{	
	//+-------------+
	//| T I M E R 0 |
	//+-------------+
	if (INTCONbits.T0IF) 			
	{								
		INTCONbits.T0IF = 0;
		
		TMR0L += 7; // TMR0 recarga cada 1ms
		Tasks1ms();
		
		if (!--TMRx10ms) 
		{
			TMRx10ms = 10;
			Tasks10ms();
					
			if (!--TMRx100ms) 
			{
				TMRx100ms = 10;
				Tasks100ms();
			
				if (!--TMRx1s) 
				{
					char i;
					TMRx1s = 10;
					Tasks1seg();
					
					if (!--TMRx1min)
					{
						TMRx1min = 60;
						//Tasks1min();
														
						if (!--TMRx1h)
						{
							TMRx1h = 60;
							//Tasks1h();	
													
							if (!--TMRx1d)
							{
								TMRx1d = 24;
								//Tasks1d();
								
							}
						}
					}
				}
			}
		}
	} 
	


	
	//+-------------+
	//| T I M E R 1 |
	//+-------------+
	if(PIR1bits.TMR1IF)
	{
		PIR1bits.TMR1IF = 0;		
		
		TMR1H = 0xFC;		
		TMR1L += 0X18;
		/////////////////////////////
		//  100 us TASKS           //
		/////////////////////////////		
		
	} 



	
	//+-----------------------------+
	//| U A R T   I N T E R R U P T |
	//+-----------------------------+
	/// <h1>Interrupción por UART</h1>
	if (PIR1bits.RCIF) 
	{
		Reader_isrUart(&reader1);
	} 		
}



/*################################################
 #                                               #
 #                     1 ms                      #
 #                                               #
 ################################################*/
void Tasks1ms()
{
	/////////////////////	
	//      1 ms       //
	/////////////////////
	
	Delayer_update(&myDelay);
	Reader_isrTmr(&reader1);
	
}//




/*################################################
 #                                               #
 #                   10 ms                       #
 #                                               #
 ################################################*/
void Tasks10ms()
{
/** <h3>Periodic Tasks: 10ms</h3> */
	
	/*************************************************
	 *                                               *
	 *          FRAME or OVERFLOW ERRORS             *
	 *                                               *
	 *************************************************/
	if (RCSTA & 0b00000110) 				
	{
		RCSTAbits.CREN = 0;
		RCSTAbits.CREN = 1;
		PIE1bits.RCIE = 1;
	}	
}//



/*################################################
 #                                               #
 #                   100 ms                      #
 #                                               #
 ################################################*/
void Tasks100ms(void)
{

	
}//



/*################################################
 #                                               #
 #                   1 seg                       #
 #                                               #
 ################################################*/

void Tasks1seg()
{
	//
}
