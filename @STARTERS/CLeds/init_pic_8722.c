//+--------------------------------------------------------------------------+
//|       $Workfile:: init_pic_8722.c            $ $Revision:: 9             $
//+--------------------------------------------------------------------------+
//|         $Author:: valdez                                                 $
//|        $Modtime:: 4/04/12 2:33p                                          $
//|        $Archive:: /@C18/SRC/Explorer1/init_pic_8722.c                    $
//+--------------------------------------------------------------------------+
/*
		 ____  ___  ____    _   ___   _____    ___  _____  ____   ____  
		|  _ \|_ _|/ ___|  / | ( _ ) |  ___|  ( _ )|___  ||___ \ |___ \ 
		| |_) || || |      | | / _ \ | |_     / _ \   / /   __) |  __) |
		|  __/ | || |___   | || (_) ||  _|   | (_) | / /   / __/  / __/ 
		|_|   |___|\____|  |_| \___/ |_|      \___/ /_/   |_____||_____|
		                                                                
		<<<<<<<<<<<<<<<<   VER HEADER p18f8722_defs.h  >>>>>>>>>>>>>>>>
*/    
#include <p18cxxx.h>				
#include "p18fxxx_defs.h"				
#include "init_pic.h" 


/**************************************************************************//** 
* @Descripcion	Inicialización de registros SFR 
* @param[in]	void
* @return		void
* @note 		Reemplaza a Visual Initialization
********************************************************************************/
void InitSFR(void)
{
	unsigned char dummy;	// Para vaciar buffer UART
	
	/*+----------------------------------------------------------------------------+
	  | Disable Interrupts during configuration                                    |
	  +----------------------------------------------------------------------------+ */

	//INTCONbits.GIE = 0;
													
	//PIE1 = 0;								
	//PIE2 = 0;											
	//PIE3 = 0;

/*						        _ _       _             
			 	  ___  ___  ___(_) | __ _| |_ ___  _ __ 
				 / _ \/ __|/ __| | |/ _` | __/ _ \| '__|
				| (_) \__ \ (__| | | (_| | || (_) | |   
				 \___/|___/\___|_|_|\__,_|\__\___/|_| 						  */
			
	OSCCON =    SLEEP_ON_SLEEP & 
			 	CLK_INT &
			 	INTOSC_8;			
	
	
	
/*				 _      _            _                    
				| |__  | |__   __ __| |  ___  ___   _ __  
				| '_ \ | |\ \ / // _` | / __|/ _ \ | '_ \ 
				| | | || | \ V /| (_| || (__| (_) || | | |
				|_| |_||_|  \_/  \__,_| \___|\___/ |_| |_|
				 HIGH/LOW-VOLTAGE DETECT CONTROL REGISTER				  	  */

	HLVDCON = HLVD_OFF;


/*
					              _  _                     
				__      __ __| || |_  ___  ___   _ __  
				\ \ /\ / // _` || __|/ __|/ _ \ | '_ \ 
				 \ V  V /| (_| || |_| (__| (_) || | | |
				  \_/\_/  \__,_| \__|\___|\___/ |_| |_|
					WATCHDOG TIMER CONTROL REGISTER  					 	  */

	WDTCON = SWDT_OFF;


/*
				 _ __  ___  ___   _ __  
				| '__|/ __|/ _ \ | '_ \ 
				| |  | (__| (_) || | | |
				|_|   \___|\___/ |_| |_|			                        
				 RESET CONTROL REGISTER									  	  */
					 
	RCON = IPEN_OFF | BOR_OFF;
	

/*						
				 ____  _____ ____   ____ ___  ____  
				|    \| ___ |    \ / ___) _ \|  _ \ 
				| | | | ____| | | ( (__| |_| | | | |
				|_|_|_|_____)_|_|_|\____)___/|_| |_|
				EXTERNAL MEMORY BUS CONTROL REGISTER						  */
						
	MEMCON = EBDISABLE;						

/*				 _                          _       
				(_) ___    _ __   ___  _ __| |_ ___ 
				| |/ _ \  | '_ \ / _ \| '__| __/ __|
				| | (_) | | |_) | (_) | |  | |_\__ \
				|_|\___/  | .__/ \___/|_|   \__|___/
				          |_|                           					  */
// 	VER io_cfg.h !!!

	PORTA = 0x00;
	TRISA = 0b11110011; 

	PORTB = 0x00;
	TRISB = 0b11111111;  //ATN!: RB0 conectado a SW1, no tocar.
	
	PORTC = 0x00;
	TRISC = 0b11010111;
	
	PORTD = 0x00;
	TRISD = 0b00000000;

	PORTE = 0x00;
	TRISE = 0b11111111; 
	
	PORTF = 0x00;
	TRISF = 0b10111111; 

	PORTG = 0x00;
	TRISG = 0b11111111; 

	PORTH = 0x00;
	TRISH = 0b11111111; 
	
	PORTJ = 0x00;
	TRISJ = 0b11111111; 
		
	/*+----------------------------------------------------------------------------+
	  | CCP configuration                                                          |
	  +----------------------------------------------------------------------------+ */

//	(CON)B5:4=DCB1:0 B4:0=CCPM3:0
	CCPR1H = 0;
	CCPR1L = 0;
	CCP1CON = 0;

//	(CON)B5:4=DCB1:0 B4:0=CCPM3:0
	CCPR2H = 0;
	CCPR2L = 0;
	CCP2CON = 0;
	
		
	/*+----------------------------------------------------------------------------+
	  | RX/TX buffer                                                               |
	  +----------------------------------------------------------------------------+ */
//	Address register (I2C Slave) or BRG (I2C Master)
	SSPADD = 0;

//	B7=SMP B6=CKE B5=D/A-L B4=P B3=S B2=R/W-L B1=UA B0=BF
	SSPSTAT = 0;

//	B7=WCOL B6=SSPOV B5=SSPEN B4=CKP B3:0=SSPM3:0
	SSPCON1 = 0;

//	B7=GCEN B6=ACKSTAT B5=ACKDT B4=ACKEN B3=RCEN B2=PEN B1=RSEN B0=SEN
	SSPCON2 = 0;

/*      
					                  	  _   
				 _   _  ___   __ _  _ __ | |_ 
				| | | |/ __| / _` || '__|| __|
				| |_| |\__ \| (_| || |   | |_ 
				 \__,_||___/ \__,_||_|    \__| 								  */ 
				 
	RCSTA1 = SPEN_ON | CREN_ON; 			// set up receive options
	TXSTA1 = TXEN_ON | BRGH_HI; 			// set up transmit options

	RCSTA2 = SPEN_OFF;			 			// set up receive options
	TXSTA2 = TXEN_OFF;			 			// set up transmit options
		
    /* para <SPBRGH1>=1, [SPBRG] = Fosc[Hz]/(16·(baudrate[Baud] + 1))
	SPBRG1 = 8000000 /(16·(9601)) = d'52'*/
	SPBRG1 = 52;				
	
	dummy = RCREG1;          // flush receive buffer uart #1
	dummy = RCREG1;
	
/*
			     _                                         __  _        
			  __| |  __ _   __ _        ___  ___   _ __   / _|(_)  __ _ 
			 / _` | / _` | / _` |      / __|/ _ \ | '_ \ | |_ | | / _` |
			| (_| || (_| || (_| |     | (__| (_) || | | ||  _|| || (_| |
			 \__,_| \__,_| \__, |      \___|\___/ |_| |_||_|  |_| \__, |
			                  |_|                                 |___/ 	  */                  
			                  
	TRISAbits.TRISA0 = 1;	     /* AD requires INPUT pin direction */
	
	
	ADCON1 = 		VCFG1_VSS & 	// Referencia-  VSS
					VCFG0_VDD & 	// Referencia+  VDD
					A1_D15;			// Sólo AN0 analógico

	ADCON0 = 		AD_CH0;			// Preparar Canal 0 para muestreo 
					
	ADCON2 = 		AD_RIGHT & 		// Right Justif
					ACQT_20  &		// Acquisition Time 0
					ADCS_FRC;		// CS: interno
	
/*				 	 _                                
					(_)       _                     
					 _ ____ _| |_ ____ ___  ____    
					| |  _ (_   _) ___) _ \|  _ \   
					| | | | || |( (__| |_| | | | |  
					|_|_| |_| \__)____)___/|_| |_|  
					 INTERRUPT CONTROL REGISTER 1				              */

	INTCON = PEIE_ON | TMR0IE_ON | GIE_ON; 

/*				 _                               ______  
				(_)       _                     (_____ \ 
				 _ ____ _| |_ ____ ___  ____      ____) )
				| |  _ (_   _) ___) _ \|  _ \    / ____/ 
				| | | | || |( (__| |_| | | | |  | (_____ 
				|_|_| |_| \__)____)___/|_| |_|  |_______)
					 INTERRUPT CONTROL REGISTER 2				              */

	INTCON2 = 0x00;
	
/*
				 _                               ______  
				(_)       _                     (_____ \ 
				 _ ____ _| |_ ____ ___  ____     _____) )
				| |  _ (_   _) ___) _ \|  _ \   (_____ ( 
				| | | | || |( (__| |_| | | | |   _____) )
				|_|_| |_| \__)____)___/|_| |_|  (______/ 
					 INTERRUPT CONTROL REGISTER 3				              */
					 
	INTCON3 = 0x00;		// 0xC0;					 
					 

/*	
				 _    _                             
				| |_ (_) _ __ ___    ___  _ __  ___ 
				| __|| || '_ ` _ \  / _ \| '__|/ __|
				| |_ | || | | | | ||  __/| |   \__ \
				 \__||_||_| |_| |_| \___||_|   |___/							  		*/

	/*+----------------------------------------------------------------------------+
	  | Timer0 - Timers configuration                                              |
	  +----------------------------------------------------------------------------+*/
//	(CON)B7=TMRON B6=T8BIT B5=TCS B4=TSE B3=PSA B<2:0>=TPS<2:0>                |
	T0CONbits.TMR0ON = 0b0;		//detener...
//	T0CON = 0b11010010;			//...y reiniciar; TPS = 8·x, 8bit wide (Tc=4us, INT=1000us)
	T0CON = 	T0_ON & 
				T0_8BIT & 
				T0_CS_INT & 
				T0_SE_DOWN & 
				T0_PS_8;
	
	TMR0H = 0;		// preset timer values
	TMR0L = 0;  	// note: must reload 0x100-TMR in application code

	/*+----------------------------------------------------------------------------+
	  | Feature=Timer1 - Timers configuration                                      |
	  +----------------------------------------------------------------------------+*/
	
//	(CON)B7=RD16 B5:4=TCKPS1:0 B3=TOSCEN B2=TSYNC-L B1=TMRCS B0=TMRON
	T1CONbits.TMR1ON = 0b0;
//	T1CON = 0b00000101;	
	T1CON = 	RD16_OFF & 
				T1_PS_1 & 
				T1_DISABLED & 
				T1_SYNC_OFF & 
				T1_CS_INT & 
				T1_ON;

	TMR1H = 0;		// preset timer values
	TMR1L = 0;		// note: must reload 0x100-TMR in application code

	/*+----------------------------------------------------------------------------+
	  | Feature=Timer2 - Timers configuration                                      |
	  +----------------------------------------------------------------------------+ */

//	(CON)B6:3=TOUTPS3:0 B2=TMRON B1:0=TCKPS1:0
//	(TMR)Timer register (cleared)
//	(PR)Timer preload register (set)

	T2CONbits.TMR2ON = 0b0;
	T2CON = 0x00;                        // set options with timer on/off (bit2)
	TMR2 = 0x00;                         			      // preset timer values
	PR2 = 0xFF;											 // preload timer values

	/*+----------------------------------------------------------------------------+
	  | ture=Timer3 - Timers configuration                                         |
	  +----------------------------------------------------------------------------+ */

//	(CON)B7=RD16 B5:4=TCKPS1:0 B3=TOSCEN B2=TSYNC-L B1=TMRCS B0=TMRON
	T3CONbits.TMR3ON = 0b0;
	T3CON = 0x00;                        // set options with timer on/off (bit0)
//	***note: must reload 0x100-TMR in application code***

	TMR3H = 0x00;								          // preset timer values
	TMR3L = 0x00;

/*
			 _         _                                   _        
			(_) _ __  | |_  ___  _ __  _ __  _   _  _ __  | |_  ___ 
			| || '_ \ | __|/ _ \| '__|| '__|| | | || '_ \ | __|/ __|
			| || | | || |_|  __/| |   | |   | |_| || |_) || |_ \__ \
			|_||_| |_| \__|\___||_|   |_|    \__,_|| .__/  \__||___/
			                                       |_|              		  */                    

	RCON = IPEN_OFF | BOR_OFF;
	PIE1 = EUSART_RX_ON | TMR1IE_ON;
	PIE2 = 0x00;
	PIE3 = 0x00;
	INTCON  = PEIE_ON | TMR0IE_ON | GIE_ON; 
	INTCON2 = 0x00; 
	INTCON3 = 0x00; 
}//




