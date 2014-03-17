//+--------------------------------------------------------------------------+
//|       $Workfile:: init_pic.c                 $ $Revision:: 2             $
//+--------------------------------------------------------------------------+
//|         $Author:: Mav                                                    $
//|        $Modtime:: 16/06/11 7:16p                                         $
//|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/init_pic.c   $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>					// definiciones Microchip
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

	INTCONbits.GIE = 0;
	
// 	B4=EE B3=BCL B2=LVD B1=TMR3 B0=CCP2                                        |
	PIE2 = 0;

// 	B7=PSP B6=AD B5=RC1 B4=TX1 B3=SSP B2=CCP1 B1=TMR2 B0=TMR1
	PIE1 = 0;

	/*+----------------------------------------------------------------------------+
	  | Oscillator configuration                                                   |
	  +----------------------------------------------------------------------------+ */

//  B0=SCS
	OSCCON = 	SLEEP_ON_SLEEP & 
			 	CLK_INT &
			 	INTOSC_8;			// == 0b01111111
	
	/*+----------------------------------------------------------------------------+
	  | Reset configuration                                                        |
	  +----------------------------------------------------------------------------+ */

//  B5=IRVST B4=LVDEN B3:0=LVDL3:0
	LVDCON = 0x01;

//	B5=IRVST B4=LVDEN B3:0=LVDL3:0
	WDTCON = 0;

//	B7=IPEN B6=LWRT B4=RI-L B3=TO-L B2=PD-L B1=POR-L B0=BOR-L
	RCON = 0x83;
	

	/*+----------------------------------------------------------------------------+
	  | IO Ports configuration                                                     |
	  +----------------------------------------------------------------------------+ */

//  |NC      |NC      |EXT_EN  |EXT_DT  |EXT_CK  |Z8      |Z7      |BATT    |
//  |7       |6       |5       |4       |3       |2       |1       |0       |

	PORTA = 0x00;
	TRISA = 0b11111111;

//  |PGD     |PGC     |BUZZER  |TSW-1   |LEDS    |LEDS    |LEDS    |LEDS    |
//  |7       |6       |5       |4       |3       |2       |1       |0       |
	PORTB = 0x00;
	TRISB = 0b11010000;  
	
    /* El puerto PORTC incluye a todas las zonas más los pines de 
    comunicación RS-232 con el modem */
//  |RX      |TX      |Z5      |Z4      |Z3      |Z2      |Z1      |Z0      |
//  |7       |6       |5       |4       |3       |2       |1       |0       | 
	TRISC = 0b11111111;
	
	/* Todos los pines del PORTD son para SPRG (antes, solamente
	los pines RD4:7) */
//  |        |S6      |S5      |S4      |S3      |S2      |S1      |S0      |
//  |7       |6       |5       |4       |3       |2       |1       |0       |
	PORTD = 0x00;
	TRISD = 0b00000000;
		
	/*IMPORTANTE: los bits 4:7 deben colocarse a 0 para 
	modo DIGITAL */
//  |DIG     |DIG     |DIG     |DIG     |MCLR_   |AUX     |-       |RING-IN |
//  |7       |6       |5       |4       |3       |2       |1       |0       |
	PORTE = 0x00;
	TRISE = 0b00001101; 

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

	/*+-----------------------------------------------------------------------------+
	  | USART configuration                                                         |
	  +-----------------------------------------------------------------------------+ */
		 
 //	(RCSTA)	B7=SPEN B6=RX9 B5=SREN B4=CREN B3=ADDEN    B2=FERR B1=OERR B0=RX9D    
	RCSTA = 0b10010000;		// set up receive options
	
 //	(TXSTA)	B7=CSRC B6=TX9 B5=TXEN B4=SYNC  B2=BRGH B1=TRMT B0=TX9D  
	TXSTA = 0b00100110;		// set up transmit options
	
    /* para <SPBRGH>=1, [SPBRG] = Fosc[Hz]/(16·(baudrate[Baud] + 1))
	SPBRG = 8000000 /(16·(9601)) = d'52'*/
	SPBRG = 52;				
	
	dummy = RCREG;          // flush receive buffer
	dummy = RCREG;

	/*+----------------------------------------------------------------------------+
	  | A2D configuration                                                          |
	  +----------------------------------------------------------------------------+ */
	TRISAbits.TRISA0 = 1;	     /* AD requires INPUT pin direction */
	
	ADCON0 = 		AD_ON_CH0;
	
	ADCON1 = 		VCFG1_VSS & 
					VCFG0_VDD & 
					A1_D11;
					
	ADCON2 = 		AD_RIGHT &
					ACQT_20 &
					ADCS_FRC;
	
	PIE1bits.ADIE = 0;			    /* no Habilitar interrupcion AD */	

	
	/*+----------------------------------------------------------------------------+
	  | interrupt priorities                                                       |
	  +----------------------------------------------------------------------------+ */

//	B4=EE B3=BCL B2=LVD B1=TMR3 B0=CCP2
	IPR2 = 0xFF;

// B7=PSP B6=AD B5=RC1 B4=TX1 B3=SSP B2=CCP1 B1=TMR2 B0=TMR1
	IPR1 = 0xFF;

//	clear int flags
//	B4=EE B3=BCL B2=LVD B1=TMR3 B0=CCP2
	PIR2 = 0;

//	B7=PSP B6=AD B5=RC1 B4=TX1 B3=SSP B2=CCP1 B1=TMR2 B0=TMR1
	PIR1 = 0;

	/*+----------------------------------------------------------------------------+
	  | global and external interrupt enables                                      |
	  +----------------------------------------------------------------------------+ */

//	B7=GIE B6=PEIE B5=TMR0IE B4=INTOIE B3=RBIE B2=TMR0IF B1=INTOIF B0=RBIF
	INTCON = 0b01100000;		// Se inhabilita TMR0IE Y GIE por ahora...

//	B7=RBPU-L B6:3=INTEDG0:3 B2=TMR0IP B1=INT3IP B0=RBIP
	INTCON2 = 0xFF;

//	B7:6=INT2:1IP B5:3=INT3:1IE B2:0=INT3:1IF
	INTCON3 = 0xC0;

	
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
	T2CON = 0;                             // set options with timer on/off (bit2)
	TMR2 = 0;                              // preset timer values
	PR2 = 0xFF;								// preload timer values

	/*+----------------------------------------------------------------------------+
	  | ture=Timer3 - Timers configuration                                         |
	  +----------------------------------------------------------------------------+ */

//	(CON)B7=RD16 B5:4=TCKPS1:0 B3=TOSCEN B2=TSYNC-L B1=TMRCS B0=TMRON
	T3CONbits.TMR3ON = 0b0;
	T3CON = 0;                             // set options with timer on/off (bit0)
//	***note: must reload 0x100-TMR in application code***

	TMR3H = 0;							   // preset timer values
	TMR3L = 0;

	/*+----------------------------------------------------------------------------+
	  | Feature=Interrupts - enable interrupts                                     |
	  +----------------------------------------------------------------------------+*/
    
//	B4=EE B3=BCL B2=LVD B1=TMR3 B0=CCP2
	PIE2 = 0;

//	B7=PSP B6=AD B5=RC1 B4=TX1 B3=SSP B2=CCP1 B1=TMR2 B0=TMR1    
//	PIE1 = 0b00100001;		// habilitar  RC1 (1 = Enables the EUSART receive interrupt) y TMR1
	PIE1 = EUSART_RX_ON | TMR1IE_ON;
	
	INTCONbits.GIE = 1;
}//




