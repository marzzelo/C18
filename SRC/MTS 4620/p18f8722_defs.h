//;+------------------------------------------------------------------+
//;|       $Workfile:: p18f8722_defs.h            $ $Revision:: 9     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 2/12/13 12:33                                  $
//;|        $Archive:: /@C18/SRC/MTS 4620/p18f8722_defs.h             $
//;+------------------------------------------------------------------+

/*
		 ____  ___  ____    _   ___   _____    ___  _____  ____   ____  
		|  _ \|_ _|/ ___|  / | ( _ ) |  ___|  ( _ )|___  ||___ \ |___ \ 
		| |_) || || |      | | / _ \ | |_     / _ \   / /   __) |  __) |
		|  __/ | || |___   | || (_) ||  _|   | (_) | / /   / __/  / __/ 
		|_|   |___|\____|  |_| \___/ |_|      \___/ /_/   |_____||_____|
           PIC 18F8722 - Definiciones para carga directa de registros 		  


  				                   _  _         _               
				  ___   ___   ___ (_)| |  __ _ | |_  ___   _ __ 
				 / _ \ / __| / __|| || | / _` || __|/ _ \ | '__|
				| (_) |\__ \| (__ | || || (_| || |_| (_) || |   
				 \___/ |___/ \___||_||_| \__,_| \__|\___/ |_|   			  
						 OSCILLATOR CONTROL REGISTER				 		  */
				                                                                                              
// para OSCCON

// A. Comportamiento frente a SLEEP
#define IDLE_ON_SLEEP 		0b11111111      // Device enters Idle mode on SLEEP instruction
#define SLEEP_ON_SLEEP 		0b01111111		// Device enters Sleep mode on SLEEP instruction

// B. Clock source Select
#define CLK_INT				0b11111111		// Internal oscillator (Ver opciones C)
#define CLK_TMR1			0b11111101		// Timer1 oscillator (SECONDARY SOURCE)
#define CLK_OSC				0b11111100		// Primary oscillator (PRIMARY SOURCE)

// C. Prescaler (válido solamente para modo CLK_INT)
#define INTOSC_8			0b11111111		// 8 MHz (INTOSC drives clock directly)
#define INTOSC_4			0b11101111		// 4 MHz
#define INTOSC_2			0b11011111		// 2 MHz
#define INTOSC_1	 		0b11001111		// 1 MHz
#define INTOSC_500			0b10111111		// 500 kHz
#define INTOSC_250			0b10101111		// 250 kHz
#define INTOSC_125			0b10011111		// 125 kHz
#define INTOSC_31			0b10001111		// 31 kHz (from either INTOSC/256 or INTRC directly)
											// Source selected by the INTSRC bit (OSCTUNE<7>), see text.
/*
					 _    _                           ___  
					| |_ (_) _ __ ___    ___  _ __   / _ \ 
					| __|| || '_ ` _ \  / _ \| '__| | | | |
					| |_ | || | | | | ||  __/| |    | |_| |
					 \__||_||_| |_| |_| \___||_|     \___/ 					  
					 														  */
// Para T0CON, elegir uno de cada categoría:

// A. ON/OFF 
#define T0_ON				0xFF			// Enables Timer0
#define T0_OFF				0b01111111		// Stops Timer0

// B. 8 / 16 BITS
#define T0_8BIT				0xFF			// Timer0 is configured as an 8-bit timer/counter
#define T0_16BIT			0b10111111		// Timer0 is configured as a 16-bit timer/counter

// C. Clock Source Selection
#define T0_CS_EXT			0xFF			// Transition on T0CKI pin
#define T0_CS_INT			0b11011111		// Internal instruction cycle clock (CLKO)

// D. Edge Selection
#define T0_SE_DOWN			0xFF			// Increment on high-to-low transition on T0CKI pin
#define T0_SE_UP			0b11101111		// Increment on low-to-high transition on T0CKI pin

// E. Prescaler Value
#define T0_PS_1				0xFF			// TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
#define T0_PS_2				0b11110000		// 1:2 Prescale value
#define T0_PS_4				0b11110001		// 1:4 Prescale value
#define T0_PS_8				0b11110010		// 1:8 Prescale value
#define T0_PS_16			0b11110011		// 1:16 Prescale value
#define T0_PS_32			0b11110100		// 1:32 Prescale value
#define T0_PS_64			0b11110101		// 1:64 Prescale value
#define T0_PS_128			0b11110110		// 1:128 Prescale value
#define T0_PS_256			0b11110111		// 1:256 Prescale value

/*
					 _    _                          _ 
					| |_ (_) _ __ ___    ___  _ __  / |
					| __|| || '_ ` _ \  / _ \| '__| | |
					| |_ | || | | | | ||  __/| |    | |
					 \__||_||_| |_| |_| \___||_|    |_|
                     	 TIMER1 CONTROL REGISTER 						 	  */
// Para T1CON, elegir uno de cada categoría:

// A. 	bit 7 		RD16: 16-Bit Read/Write Mode Enable bit 
#define RD16_ON				0xFF			// 1 = Enables register read/write of TImer1 in one 16-bit operation
#define RD16_OFF			0b01111111		// 0 = Enables register read/write of Timer1 in two 8-bit operations

// B. 	bit 6 		READ/ONLY

// C. 	bit 5-4 	T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits
#define T1_PS_8  			0xFF			// 11 = 1:8 Prescale value
#define T1_PS_4  			0b11101111		// 10 = 1:4 Prescale value
#define T1_PS_2  			0b11011111		// 01 = 1:2 Prescale value
#define T1_PS_1  			0b11001111		// 00 = 1:1 Prescale value

// D. 	bit 3 		T1OSCEN: Timer1 Oscillator Enable bit
#define T1_ENABLED			0xFF			// 1 = Timer1 oscillator is enabled
#define T1_DISABLED			0b11110111		// 0 = Timer1 oscillator is shut off

// E. 	bit 2 		T1SYNC: Timer1 External Clock Input Synchronization Select bit
#define T1_SYNC_OFF			0xFF			// 1 = Do not synchronize external clock input
#define T1_SYNC_ON			0b11110000		// 0 = Synchronize external clock input

// F. 	bit 1 		TMR1CS: Timer1 Clock Source Select bit
#define T1_CS_EXT			0xFF      		// 1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge)
#define T1_CS_INT			0b11111101		// 0 = Internal clock (FOSC/4)

// G.	bit 0 		TMR1ON: Timer1 On bit
#define T1_ON				0xFF			// 1 = Enables Timer1
#define T1_OFF				0b11111110		// 0 = Stops Timer1

/*
					       _                      ______  
					   _  (_)                    (_____ \ 
					 _| |_ _ ____  _____  ____     ____) )
					(_   _) |    \| ___ |/ ___)   / ____/ 
					  | |_| | | | | ____| |      | (_____ 
					   \__)_|_|_|_|_____)_|      |_______)
                     	 	TIMER2 CONTROL REGISTER 					 	  */	
               	 	
//bit 7 Unimplemented: Read as ‘0’

//bit 6-3 T2OUTPS3:T2OUTPS0: Timer2 Output Postscale Select bits
//0000 = 1:1 Postscale
//0001 = 1:2 Postscale
//...
//1111 = 1:16 Postscale
#define T2OUTPS_1			0b00000000
#define T2OUTPS_2			0b00001000
#define T2OUTPS_3			0b00010000
#define T2OUTPS_4			0b00011000
#define T2OUTPS_5			0b00100000
#define T2OUTPS_6			0b00101000
#define T2OUTPS_7			0b00110000
#define T2OUTPS_8			0b00111000
#define T2OUTPS_9			0b01000000
#define T2OUTPS_10			0b01001000
#define T2OUTPS_11			0b01010000
#define T2OUTPS_12			0b01011000
#define T2OUTPS_13			0b01100000
#define T2OUTPS_14			0b01101000
#define T2OUTPS_15			0b01110000
#define T2OUTPS_16			0b01111000

//bit 2 TMR2ON: Timer2 On bit
//1 = Timer2 is on
//0 = Timer2 is off
#define TMR2_ON				0b00000100
#define TMR2_OFF			0x00


//bit 1-0 T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits
//00 = Prescaler is 1
//01 = Prescaler is 4
//1x = Prescaler is 16          
#define T2CKPS_1           	0b00000000
#define T2CKPS_4           	0b00000001
#define T2CKPS_16          	0b00000010
                     	 						                                      
/*
						 _         _                     
						(_) _ __  | |_  ___  ___   _ __  
						| || '_ \ | __|/ __|/ _ \ | '_ \ 
						| || | | || |_| (__| (_) || | | |
						|_||_| |_| \__|\___|\___/ |_| |_|                                 
					    INTCON: INTERRUPT CONTROL REGISTER					  */	

// IMPORTANTE:  USAR EL OPERADOR "OR" PARA SELECCIONAR ESTOS BITS!!

//bit 7 GIE/GIEH: Global Interrupt Enable bit
//When IPEN = 0:
//1 = Enables all unmasked interrupts
//0 = Disables all interrupts
//When IPEN = 1:
//1 = Enables all high-priority interrupts
//0 = Disables all interrupts
#define IPEN_ON			0b10000000
#define IPEN_OFF		0x00
#define GIE_ON			0b10000000
#define GIE_OFF			0x00

//bit 6 PEIE/GIEL: Peripheral Interrupt Enable bit
//When IPEN = 0:
//1 = Enables all unmasked peripheral interrupts
//0 = Disables all peripheral interrupts
//When IPEN = 1:
//1 = Enables all low-priority peripheral interrupts
//0 = Disables all low-priority peripheral interrupts
#define PEIE_ON			0b01000000
#define PEIE_OFF		0x00
#define GIEL_ON			0b01000000
#define GIEL_OFF		0x00

//bit 5 TMR0IE: TMR0 Overflow Interrupt Enable bit
//1 = Enables the TMR0 overflow interrupt
//0 = Disables the TMR0 overflow interrupt
#define TMR0IE_ON		0b00100000
#define TMR0IE_OFF		0x00

//bit 4 INT0IE: INT0 External Interrupt Enable bit
//1 = Enables the INT0 external interrupt
//0 = Disables the INT0 external interrupt
#define INT0IE_ON		0b00010000
#define INT0IE_OFF		0x00

//bit 3 RBIE: RB Port Change Interrupt Enable bit
//1 = Enables the RB port change interrupt
//0 = Disables the RB port change interrupt
#define RBIE_ON			0b00001000
#define RBIE_OFF		0x00

/*				 _                               ______  
				(_)       _                     (_____ \ 
				 _ ____ _| |_ ____ ___  ____      ____) )
				| |  _ (_   _) ___) _ \|  _ \    / ____/ 
				| | | | || |( (__| |_| | | | |  | (_____ 
				|_|_| |_| \__)____)___/|_| |_|  |_______)
					 INTERRUPT CONTROL REGISTER 2				              */

//	bit 7 RBPU: PORTB Pull-up Enable bit
//	1 = All PORTB pull-ups are disabled
//	0 = PORTB pull-ups are enabled by individual port latch values
#define RBPU_ON			0b10000000
#define RBPU_OFF		0x00

//	bit 6 INTEDG0: External Interrupt 0 Edge Select bit
//	1 = Interrupt on rising edge
//	0 = Interrupt on falling edge
#define INTEDG0_UP		0b01000000
#define INTEDG0_DOWN	0x00

//	bit 5 INTEDG1: External Interrupt 1 Edge Select bit
//	1 = Interrupt on rising edge
//	0 = Interrupt on falling edge
#define INTEDG1_UP		0b00100000
#define INTEDG1_DOWN	0x00

//	bit 4 INTEDG2: External Interrupt 2 Edge Select bit
//	1 = Interrupt on rising edge
//	0 = Interrupt on falling edge
#define INTEDG2_UP		0b00010000
#define INTEDG2_DOWN	0x00

//	bit 3 INTEDG3: External Interrupt 3 Edge Select bit
//	1 = Interrupt on rising edge
//	0 = Interrupt on falling edge
#define INTEDG3_UP		0b00001000
#define INTEDG3_DOWN	0x00

//	bit 2 TMR0IP: TMR0 Overflow Interrupt Priority bit
//	1 = High priority
//	0 = Low priority
#define TMR0IP_HI 		0b00000100
#define TMR0IP_LO		0x00

//	bit 1 INT3IP: INT3 External Interrupt Priority bit
//	1 = High priority
//	0 = Low priority
#define INT3IP_HI 		0b00000010
#define INT3IP_LO		0x00

//	bit 0 RBIP: RB Port Change Interrupt Priority bit
//	1 = High priority
//	0 = Low priority
#define RBIP_HI			0b00000001
#define RBIP_LO			0x00

/*
				 _                               ______  
				(_)       _                     (_____ \ 
				 _ ____ _| |_ ____ ___  ____     _____) )
				| |  _ (_   _) ___) _ \|  _ \   (_____ ( 
				| | | | || |( (__| |_| | | | |   _____) )
				|_|_| |_| \__)____)___/|_| |_|  (______/ 
					 INTERRUPT CONTROL REGISTER 3				              */

//	bit 7 INT2IP: INT2 External Interrupt Priority bit
//	1 = High priority
//	0 = Low priority
#define INT2IP_HI		0b10000000
#define INT2IP_LO		0x00

//	bit 6 INT1IP: INT1 External Interrupt Priority bit
//	1 = High priority
//	0 = Low priority
#define INT1IP_HI		0b01000000
#define INT1IP_LO		0x00

//	bit 5 INT3IE: INT3 External Interrupt Enable bit
//	1 = Enables the INT3 external interrupt
//	0 = Disables the INT3 external interrupt
#define INT3IE_ON		0b00100000
#define INT3IE_OFF		0x00

//	bit 4 INT2IE: INT2 External Interrupt Enable bit
//	1 = Enables the INT2 external interrupt
//	0 = Disables the INT2 external interrupt
#define INT2IE_ON		0b00010000
#define INT2IE_OFF		0x00

//	bit 3 INT1IE: INT1 External Interrupt Enable bit
//	1 = Enables the INT1 external interrupt
//	0 = Disables the INT1 external interrupt
#define INT1IE_ON		0b00001000
#define INT1IE_OFF		0x00

/*						
						 ____  _____ ____   ____ ___  ____  
						|    \| ___ |    \ / ___) _ \|  _ \ 
						| | | | ____| | | ( (__| |_| | | | |
						|_|_|_|_____)_|_|_|\____)___/|_| |_|
						EXTERNAL MEMORY BUS CONTROL REGISTER				  */
							
//	bit 7 EBDIS: External Bus Disable bit
//	1 = External bus enabled when microcontroller accesses external memory;
//	otherwise, all external bus drivers are mapped as I/O ports
//	0 = External bus always enabled, I/O ports are disabled
#define EBDISABLE		0b10000000
#define EBENABLE		0x00

//	bit 6 Unimplemented: Read as ‘0’

//	bit 5-4 WAIT1:WAIT0: Table Reads and Writes Bus Cycle Wait Count bits
//	11 = Table reads and writes will wait 0 TCY
//	10 = Table reads and writes will wait 1 TCY
//	01 = Table reads and writes will wait 2 TCY
//	00 = Table reads and writes will wait 3 TCY
#define WAIT_0TCY		0b00110000
#define WAIT_1TCY		0b00100000
#define WAIT_2TCY		0b00010000
#define WAIT_3TCY		0x00

//	bit 3-2 Unimplemented: Read as ‘0’

//	bit 1-0 WM1:WM0: TBLWT Operation with 16-bit Data Bus Width Select bits
//	1x = Word Write mode: TABLAT0 and TABLAT1 word output, WRH active when
//	TABLAT1 written
//	01 = Byte Select mode: TABLAT data copied on both MSB and LSB, WRH and (UB or LB)
//	will activate
//	00 = Byte Write mode: TABLAT data copied on both MSB and LSB, WRH or WRL will activate						

/*
                                         _         
						 _ __  ___  ___ | |_  __ _ 
						| '__|/ __|/ __|| __|/ _` |
						| |  | (__ \__ \| |_| (_| |
						|_|   \___||___/ \__|\__,_|
				 RCSTA: RECEIVE STATUS AND CONTROL REGISTER         		  */

// IMPORTANTE:  USAR EL OPERADOR "OR" PARA SELECCIONAR ESTOS BITS!!

//bit 7 SPEN: Serial Port Enable bit
//1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
//0 = Serial port disabled (held in Reset)
#define SPEN_ON			0b10000000
#define SPEN_OFF		0x00

//bit 6 RX9: 9-Bit Receive Enable bit
//1 = Selects 9-bit reception
//0 = Selects 8-bit reception
#define RX9_ON			0b01000000
#define RX9_OFF			0x00

//bit 5 SREN: Single Receive Enable bit
//Asynchronous mode: Don?t care.
//Synchronous mode ? Master:
//1 = Enables single receive
//0 = Disables single receive
//This bit is cleared after reception is complete.
//Synchronous mode ? Slave: Don?t care.
#define SREN_ON			0b00100000
#define SREN_OFF		0x00

//bit 4 CREN: Continuous Receive Enable bit
//Asynchronous mode:
//1 = Enables receiver
//0 = Disables receiver
//Synchronous mode:
//1 = Enables continuous receive until enable bit, CREN, is cleared (CREN overrides SREN)
//0 = Disables continuous receive
#define CREN_ON			0b00010000
#define CREN_OFF		0x00

//bit 3 ADDEN: Address Detect Enable bit
//Asynchronous mode 9-Bit (RX9 = 1):
//1 = Enables address detection, enables interrupt and loads the receive buffer when RSR<8> is set
//0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit
//Asynchronous mode 9-Bit (RX9 = 0): don?t care.
#define ADDEN_ON		0b00001000
#define ADDEN_OFF		0x00

//bit 2 FERR: Framing Error bit
//1 = Framing error (can be cleared by reading RCREG register and receiving next valid byte)
//0 = No framing error

/*(READ ONLY)*/

//bit 1 OERR: Overrun Error bit
//1 = Overrun error (can be cleared by clearing bit, CREN)
//0 = No overrun error

/*(READ ONLY)*/

//bit 0 RX9D: 9th Bit of Received Data
//This can be address/data bit or a parity bit and must be calculated by user firmware.

/*(READ ONLY)*/

/*
						 _               _         
						| |_ __  __ ___ | |_  __ _ 
						| __|\ \/ // __|| __|/ _` |
						| |_  >  < \__ \| |_| (_| |
						 \__|/_/\_\|___/ \__|\__,_|
			TXSTA1/TXSTA2: TRANSMIT STATUS AND CONTROL REGISTER        		  */

// IMPORTANTE:  USAR EL OPERADOR "OR" PARA SELECCIONAR ESTOS BITS!!

//bit 7 CSRC: Clock Source Select bit
//Asynchronous mode: Don?t care.
//Synchronous mode:
//1 = Master mode (clock generated internally from BRG)
//0 = Slave mode (clock from external source)
#define CSRC_INT		0b10000000
#define CSRC_EXT		0x00

//bit 6 TX9: 9-Bit Transmit Enable bit
//1 = Selects 9-bit transmission
//0 = Selects 8-bit transmission
#define TX9_ON			0b01000000
#define TX9_OFF			0x00

//bit 5 TXEN: Transmit Enable bit(1)
//1 = Transmit enabled
//0 = Transmit disabled
#define TXEN_ON			0b00100000
#define TXEN_OFF		0x00

//bit 4 SYNC: EUSART Mode Select bit
//1 = Synchronous mode
//0 = Asynchronous mode
#define SYNC_ON			0b00010000
#define SYNC_OFF		0x00

//bit 3 SENDB: Send Break Character bit
//Asynchronous mode:
//1 = Send Sync Break on next transmission (cleared by hardware upon completion)
//0 = Sync Break transmission completed
//Synchronous mode: Don?t care.
#define SENDB_ON		0b00001000
#define SEMDB_OFF		0x00

//bit 2 BRGH: High Baud Rate Select bit
//Asynchronous mode:
//1 = High speed
//0 = Low speed
//Synchronous mode: Unused in this mode.
#define BRGH_HI			0b00000100
#define BRGH_LO 		0x00

//bit 1 TRMT: Transmit Shift Register Status bit
//1 = TSR empty
//0 = TSR full

/*(READ ONLY)*/

//bit 0 TX9D: 9th Bit of Transmit Data
//Can be address/data bit or a parity bit.
//Note 1: SREN/CREN overrides TXEN in Sync mode.

/*(READ ONLY / DATA)*/

/*
						 ____  ___  _____   _ 
						|  _ \|_ _|| ____| / |
						| |_) || | |  _|   | |
						|  __/ | | | |___  | |
						|_|   |___||_____| |_|
				   P  I  E  1  -  INTERRUPT ENABLE   					      */

// IMPORTANTE:  USAR EL OPERADOR "OR" PARA SELECCIONAR ESTOS BITS!!

//	bit 7 SPPIE: Streaming Parallel Port Read/Write Interrupt Enable bit(1)
//	1 = Enables the SPP read/write interrupt
//	0 = Disables the SPP read/write interrupt
#define SPPIE_ON			0b10000000
#define SPPIE_OFF			0x00

//	bit 6 ADIE: A/D Converter Interrupt Enable bit
//	1 = Enables the A/D interrupt
//	0 = Disables the A/D interrupt
#define ADIE_ON				0b01000000
#define ADIE_OFF			0x00

//	bit 5 RCIE: EUSART Receive Interrupt Enable bit
//	1 = Enables the EUSART receive interrupt
//	0 = Disables the EUSART receive interrupt
#define EUSART_RX_ON		0b00100000
#define EUSART_RX_OFF		0x00

//	bit 4 TXIE: EUSART Transmit Interrupt Enable bit
//	1 = Enables the EUSART transmit interrupt
//	0 = Disables the EUSART transmit interrupt
#define EUSART_TX_ON		0b00010000
#define EUSART_TX_OFF		0x00

//	bit 3 SSPIE: Master Synchronous Serial Port Interrupt Enable bit
//	1 = Enables the MSSP interrupt
//	0 = Disables the MSSP interrupt
#define SSPIE_ON			0b00001000
#define SSPIE_OFF			0x00

//	bit 2 CCP1IE: CCP1 Interrupt Enable bit
//	1 = Enables the CCP1 interrupt
//	0 = Disables the CCP1 interrupt
#define CCP1IE_ON			0b00000100
#define CCP1IE_OFF			0x00

//	bit 1 TMR2IE: TMR2 to PR2 Match Interrupt Enable bit
//	1 = Enables the TMR2 to PR2 match interrupt
//	0 = Disables the TMR2 to PR2 match interrupt
#define TMR2IE_ON			0b00000010
#define TMR2IE_OFF			0x00

//bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit
//	1 = Enables the TMR1 overflow interrupt
//	0 = Disables the TMR1 overflow interrupt
#define TMR1IE_ON			0b00000001
#define TMR1IE_OFF			0x00

/*
					 ______  _ _______    ______  
					(_____ \| (_______)  (_____ \ 
					 _____) ) |_____       ____) )
					|  ____/| |  ___)     / ____/ 
					| |     | | |_____   | (_____ 
					|_|     |_|_______)  |_______)	
				PERIPHERAL INTERRUPT ENABLE REGISTER 2						  */
				
//	bit 7 OSCFIE: Oscillator Fail Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define OSCFIE_ON			0b10000000
#define OSCFIE_OFF			0x00

//	bit 6 CMIE: Comparator Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define CMIE_ON				0b01000000
#define CMIE_OFF			0x00

//	bit 5 Unimplemented: Read as ‘0’

//	bit 4 EEIE: Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define EEIE_ON				0b00010000
#define EEIE_OFF			0x00

//	bit 3 BCL1IE: MSSP1 Bus Collision Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define BCL1IE_ON			0b00001000
#define BCL1IE_OFF			0x00

//	bit 2 HLVDIE: High/Low-Voltage Detect Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define HLVDIE_ON			0b00000100
#define HLVDIE_OFF			0x00

//	bit 1 TMR3IE: TMR3 Overflow Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define TMR3IE_ON			0b00000010
#define TMR3IE_OFF			0x00


//	bit 0 CCP2IE: ECCP2 Interrupt Enable bit
//	1 = Enabled
//	0 = Disabled
#define CCP2IE_ON			0b00000001
#define CCP2IE_OFF			0x00



/*
				            _                       ___  
				  __ _   __| |  ___  ___   _ __    / _ \ 
				 / _` | / _` | / __|/ _ \ | '_ \  | | | |
				| (_| || (_| || (__| (_) || | | | | |_| |
				 \__,_| \__,_| \___|\___/ |_| |_|  \___/ 
						  A/D CONTROL REGISTER					  			  */
						  
//  +--------+--------+--------+--------+--------+--------+--------+--------+
//  |                                 ADCON0                                |
//  +--------+--------+--------+--------+--------+--------+--------+--------+
//  |U       |U       |R/W     |R/W     |R/W     |R/W     |R/W     |R/W     |
//	|0       |0       |0       |0       |0       |0       |0       |0       |
//  +--------+--------+--------+--------+--------+--------+--------+--------+
//	|   --   |   --   |CHS3    |CHS2    |CHS1    |CHS0    |GO/DONE |ADON    |
//  |7       |6       |5       |4       |3       |2       |1       |0       |
//  +--------+--------+--------+--------+--------+--------+--------+--------+

// CHS2:CHS0: Analog Channel Select bits (Forces ADON = 1)

// Nota: ver macro OpenADC(canal), reemplaza a estas definiciones
#define AD_ON_CH0				0b00000001		// Channel 0 (AN0) & ADON
#define AD_ON_CH1				0b00000101		// Channel 1 (AN1) & ADON
#define AD_ON_CH2				0b00001001		// Channel 2 (AN2) & ADON
#define AD_ON_CH3				0b00001101		// Channel 3 (AN3) & ADON
#define AD_ON_CH4				0b00010001		// Channel 4 (AN4) & ADON
#define AD_ON_CH5				0b00010101		// Channel 5 (AN5) & ADON
#define AD_ON_CH6				0b00011001		// Channel 6 (AN6) & ADON
#define AD_ON_CH7				0b00011101		// Channel 7 (AN7) & ADON
#define AD_ON_CH8				0b00100001		// Channel 8 (AN7) & ADON
#define AD_ON_CH9				0b00100101		// Channel 9 (AN7) & ADON
#define AD_ON_CH10				0b00101001		// Channel 10(AN7) & ADON
#define AD_ON_CH11				0b00101101		// Channel 11(AN7) & ADON
#define AD_ON_CH12				0b00110001		// Channel 12(AN7) & ADON
#define AD_ON_CH13				0b00110101		// Channel 13(AN7) & ADON
#define AD_ON_CH14				0b00111001		// Channel 14(AN7) & ADON
#define AD_ON_CH15				0b00111101		// Channel 15(AN7) & ADON

// Para setear ADON en tiempo posterior:
#define AD_CH0					0b00000000		// Channel 0 (AN0 = RA0) 
#define AD_CH1					0b00000100		// Channel 1 (AN1 = RA1) 
#define AD_CH2					0b00001000		// Channel 2 (AN2 = RA2) 
#define AD_CH3					0b00001100		// Channel 3 (AN3 = RA3) 
#define AD_CH4					0b00010000		// Channel 4 (AN4 = *RA5) <--
#define AD_CH5					0b00010100		// Channel 5 (AN5 = RF0) <--
#define AD_CH6					0b00011000		// Channel 6 (AN6 = RF1) 
#define AD_CH7					0b00011100		// Channel 7 (AN7 = RF2) 
#define AD_CH8					0b00100000		// Channel 8 (AN8 = RF3) 
#define AD_CH9					0b00100100		// Channel 9 (AN9 = RF4) 
#define AD_CH10					0b00101000		// Channel 10(AN10 = RF5) 
#define AD_CH11					0b00101100		// Channel 11(AN11 = RF6)
#define AD_CH12					0b00110000		// Channel 12(AN12 = *RH4) <--
#define AD_CH13					0b00110100		// Channel 13(AN13 = RH5) 
#define AD_CH14					0b00111000		// Channel 14(AN14 = RH6) 
#define AD_CH15					0b00111100		// Channel 15(AN15 = RH7) 

#define AD_OFF					0x00
#define AD_ON					0b00000001		// usar con bitOR

/*				
				            _                      _ 
				  __ _   __| |  ___  ___   _ __   / |
				 / _` | / _` | / __|/ _ \ | '_ \  | |
				| (_| || (_| || (__| (_) || | | | | |
				 \__,_| \__,_| \___|\___/ |_| |_| |_|

//  +--------+--------+--------+--------+--------+--------+--------+--------+
//  |                                 ADCON1                                |
//  +--------+--------+--------+--------+--------+--------+--------+--------+
//  |U       |U       |R/W     |R/W     |R/W     |R/W     |R/W     |R/W     |
//	|0       |0       |0       |0       |0       |*       |*       |*       |
//  +--------+--------+--------+--------+--------+--------+--------+--------+
//	|   --   |   --   |VCFG1   |VCFG0   |PCFG3   |PCFG2   |PCFG1   |PCFG0   |
//  |7       |6       |5       |4       |3       |2       |1       |0       |
//  +--------+--------+--------+--------+--------+--------+--------+--------+
/* (*)The value of the PCFG bits depends on the value of the PBADEN configuration
      bit. When PBADEN = 1, PCFG<3:0> = 0000; when PBADEN = 0, PCFG<3:0> = 0111 */

//	bit 7-6 Unimplemented: Read as '0'

//	bit 5 	VCFG1: 			Voltage Reference Configuration bit (VREF- source)
//	1 = VREF- (AN2)
//	0 = VSS
#define VCFG1_AN2			0x3F
#define VCFG1_VSS			0b00011111

//	bit 4 	VCFG0: 			Voltage Reference Configuration bit (VREF+ source)
//	1 = VREF+ (AN3)
//	0 = VDD
#define VCFG0_AN3			0x3F
#define VCFG0_VDD			0b00101111

//	bit 3-0 	PCFG3:PCFG0: 	A/D Port Configuration Control bits:	
#define A16_D0				0b00110000		// ANALOG:16, DIGITAL:0	
#define A14_D2				0b00110001		// No existe A15_D1 !!!
#define A13_D3				0b00110010						
#define A12_D4				0b00110011			
#define A11_D5				0b00110100			
#define A10_D6				0b00110101			
#define A9_D7				0b00110110			
#define A8_D8				0b00110111			
#define A7_D9				0b00111000			
#define A6_D10				0b00111001			
#define A5_D11				0b00111010			
#define A4_D12				0b00111011			
#define A3_D13				0b00111100			
#define A2_D14				0b00111101			
#define A1_D15				0b00111110			
#define A0_D16				0x3F			// ANALOG:0, DIGITAL:16

/*
					            _                      ____  
					  __ _   __| |  ___  ___   _ __   |___ \ 
					 / _` | / _` | / __|/ _ \ | '_ \    __) |
					| (_| || (_| || (__| (_) || | | |  / __/ 
					 \__,_| \__,_| \___|\___/ |_| |_| |_____|		
					                                         				  */
//	bit 7 ADFM: A/D Result Format Select bit
//	1 = Right justified
//	0 = Left justified
#define AD_RIGHT			0xFF				// Right justified
#define AD_LEFT				0b01111111			// Left justified

//	bit 6 Unimplemented: Read as '0'
//	
//	bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits
//	111 = 20 TAD
//	110 = 16 TAD
//	101 = 12 TAD
//	100 = 8 TAD
//	011 = 6 TAD
//	010 = 4 TAD
//	001 = 2 TAD
//	000 = 0 TAD(1)
#define ACQT_20					0xFF			
#define ACQT_16					0b11110111		
#define ACQT_12					0b11101111		
#define ACQT_8 					0b11100111		
#define ACQT_6 					0b11011111		
#define ACQT_4 					0b11010111		
#define ACQT_2 					0b11001111		
#define ACQT_0 					0b11000111		


//	bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits
//	111 = FRC (clock derived from A/D RC oscillator)(1)
//	110 = FOSC/64
//	101 = FOSC/16
//	100 = FOSC/4
//	011 = FRC (clock derived from A/D RC oscillator)(1) (repetido, no se define)
//	010 = FOSC/32
//	001 = FOSC/8
//	000 = FOSC/2
#define ADCS_FRC				0xFF			// FRC (clock derived from A/D RC oscillator)
#define ADCS_64					0b11111110		// Conv Clock =  2·TOSC
#define ADCS_16					0b11111101		// Conv Clock =  4·TOSC
#define ADCS_4					0b11111100		// Conv Clock =  8·TOSC
#define ADCS_32					0b11111010		// Conv Clock =  8·TOSC
#define ADCS_8 					0b11111001		// Conv Clock = 32·TOSC
#define ADCS_2 					0b11111000		// Conv Clock = 64·TOSC


/*
					 _      _            _                    
					| |__  | |__   __ __| |  ___  ___   _ __  
					| '_ \ | |\ \ / // _` | / __|/ _ \ | '_ \ 
					| | | || | \ V /| (_| || (__| (_) || | | |
					|_| |_||_|  \_/  \__,_| \___|\___/ |_| |_|
				 HLVDCON: HIGH/LOW-VOLTAGE DETECT CONTROL REGISTER			  

	R/W-0 		U-0 R-0 	R/W-0 	R/W-0 		R/W-1 		R/W-0 		R/W-1
	VDIRMAG 	— 	IRVST 	HLVDEN 	HLVDL3(1) 	HLVDL2(1) 	HLVDL1(1) 	HLVDL0(1)
	bit 7 																   bit 0
	
//	bit 7 VDIRMAG: Voltage Direction Magnitude Select bit
//	1 = Event occurs when voltage equals or exceeds trip point (HLVDL3:HLDVL0)
//	0 = Event occurs when voltage equals or falls below trip point (HLVDL3:HLVDL0) */
#define HLVDUP				0b10000000
#define HLVDDOWN			0x00

//	bit 6 Unimplemented: Read as ‘0’

//	bit 5 IRVST: Internal Reference Voltage Stable Flag bit
//	1 = Indicates that the voltage detect logic will generate the interrupt flag at 
//		the specified voltage range
//	0 = Indicates that the voltage detect logic will not generate the interrupt flag 
//		at the specified voltage range and the HLVD interrupt should not be enabled
#define HLVDFLAG_ON			0b00100000
#define HLVDFLAG_OFF		0x00

//	bit 4 HLVDEN: High/Low-Voltage Detect Power Enable bit
//	1 = HLVD enabled
//	0 = HLVD disabled
#define HLVD_ON				0b00010000
#define HLVD_OFF			0x00

//	bit 3-0 HLVDL3:HLVDL0: Voltage Detection Limit bits(1)
//	1111 = External analog input is used (input comes from the HLVDIN pin)
//	1110 = Maximum setting
//	.
//	.
//	.
//	0000 = Minimum setting
//	Note 1: See Table 28-4 for sp
#define HLVD_EXT		0b00001111
#define HLVD_15			0b00001110
#define HLVD_14			0b00001110
#define HLVD_13			0b00001101
#define HLVD_12			0b00001100
#define HLVD_11			0b00001011
#define HLVD_10			0b00001010
#define HLVD_9			0b00001001
#define HLVD_8			0b00001000
#define HLVD_7			0b00000111
#define HLVD_6			0b00000110
#define HLVD_5			0b00000101
#define HLVD_4			0b00000100
#define HLVD_3			0b00000011
#define HLVD_2			0b00000010
#define HLVD_1			0b00000001
#define HLVD_0			0x00       


/*
				              _  _                     
				__      __ __| || |_  ___  ___   _ __  
				\ \ /\ / // _` || __|/ __|/ _ \ | '_ \ 
				 \ V  V /| (_| || |_| (__| (_) || | | |
				  \_/\_/  \__,_| \__|\___|\___/ |_| |_|
					WATCHDOG TIMER CONTROL REGISTER  						  */

//	bit 0 SWDTEN: Software Controlled Watchdog Timer Enable bit(1)
//	1 = Watchdog Timer is on
//	0 = Watchdog Timer is off
//	Note 1: This bit has no effect if the configuration bit, WDTEN, is enabled.
#define SWDT_ON			0b00000001
#define SWDT_OFF		0x0

/*
					 _ __  ___  ___   _ __  
					| '__|/ __|/ _ \ | '_ \ 
					| |  | (__| (_) || | | |
					|_|   \___|\___/ |_| |_|			                        
					 RESET CONTROL REGISTER									  */

//			R/W-0 	R/W-1	 	U-0 	R/W-1 	R-1 	R-1 	R/W-0	R/W-0
//			IPEN 	SBOREN 		— 		RI 		TO 		PD 		POR 	BOR
//			bit 7 														bit 0
//			
//	bit 7 IPEN: Interrupt Priority Enable bit
//	1 = Enable priority levels on interrupts
//	0 = Disable priority levels on interrupts (PIC16CXXX Compatibility mode)	
#define IPEN_ON			0b10000000
#define IPEN_OFF		0x00

//	bit 6 SBOREN: BOR Software Enable bit(1)
//	If BOREN1:BOREN0 = 01:
//	1 = BOR is enabled
//	0 = BOR is disabled
//	If BOREN1:BOREN0 = 00, 10 or 11:
//	Bit is disabled and read as ‘0’.
#define BOR_ON			0b01000000
#define BOR_OFF			0x0
  	
//	Note 1: If SBOREN is enabled, its Reset state is ‘1’; otherwise, it is ‘0’.


/*
			 	 ____ ____  ____        ____ _____  _  _____ 
				/ ___/ ___||  _ \__  __/ ___|_   _|/ \|_   _|
				\___ \___ \| |_) \ \/ /\___ \ | | / _ \ | |  
				 ___) |__) |  __/ >  <  ___) || |/ ___ \| |  
				|____/____/|_|   /_/\_\|____/ |_/_/   \_\_|  
					MSSPx STATUS REGISTER (SPI™ MODE) */
	
//	R/W-0 	R/W-0 	R-0 	R-0 	R-0 	R-0 	R-0 	R-0
//	SMP 	CKE 	D/A 	P 		S 		R/W 	UA 		BF
//	bit 7 													bit 0
		
//	bit 7 SMP: Sample bit
//	SPI Master mode:
//	1 = Input data sampled at end of data output time
//	0 = Input data sampled at middle of data output time
//	SPI Slave mode:
//	SMP must be cleared when SPI is used in Slave mode.
#define SMP_END		0b10000000
#define SMP_MID		0x00

//	bit 6 CKE: SPI Clock Select bit
//	1 = Transmit occurs on transition from active to Idle clock state
//	0 = Transmit occurs on transition from Idle to active clock state
//	Note: Polarity of clock state is set by the CKP bit (SSPxCON1<4>).
#define TRM_ACT_IDLE	0b01000000
#define TRM_IDLE_ACT	0x00

/* 

				 ____ ____  ____        ____ ___  _   _ _ 
				/ ___/ ___||  _ \__  __/ ___/ _ \| \ | / |
				\___ \___ \| |_) \ \/ / |  | | | |  \| | |
				 ___) |__) |  __/ >  <| |__| |_| | |\  | |
				|____/____/|_|   /_/\_\\____\___/|_| \_|_|
				   MSSPx CONTROL REGISTER 1 (SPI™ MODE)  */

//			R/W-0 	R/W-0 	R/W-0 	R/W-0 	R/W-0 	R/W-0 	R/W-0 	R/W-0
//			WCOL 	SSPOV 	SSPEN 	CKP 	SSPM3 	SSPM2 	SSPM1 	SSPM0
//			bit 7 													bit 0
//	
//	bit 7 WCOL: Write Collision Detect bit
//	1 = The SSPxBUF register is written while it is still transmitting the previous word
//	(must be cleared in software)
//	0 = No collision
#define WCOL_RESET	0x00

//	bit 6 SSPOV: Receive Overflow Indicator bit
//	SPI Slave mode:
//	1 = A new byte is received while the SSPxBUF register is still holding the previous data. In case
//	of overflow, the data in SSPxSR is lost. Overflow can only occur in Slave mode. The user
//	must read the SSPxBUF, even if only transmitting data, to avoid setting overflow (must be
//	cleared in software).
//	0 = No overflow
//	Note: In Master mode, the overflow bit is not set since each new reception (and
//	transmission) is initiated by writing to the SSPxBUF register.
#define SSPOV_RESET	0x00

//	bit 5 SSPEN: Synchronous Serial Port Enable bit
//	1 = Enables serial port and configures SCKx, SDOx, SDIx and SSx as serial port pins
//	0 = Disables serial port and configures these pins as I/O port pins
//	Note: When enabled, these pins must be properly configured as input or output.
#define SSP_ENABLE 	0b00100000
#define SSP_DISABLE 0x00

//	bit 4 CKP: Clock Polarity Select bit
//	1 = Idle state for clock is a high level
//	0 = Idle state for clock is a low level
#define CKP_IDLEISHI	0b00010000
#define CKP_IDLEISLO	0x00

//	bit 3-0 SSPM3:SSPM0: Synchronous Serial Port Mode Select bits
//	0101 = SPI Slave mode, clock = SCKx pin, SSx pin control disabled, SSx can be used as I/O pin
//	0100 = SPI Slave mode, clock = SCKx pin, SSx pin control enabled
//	0011 = SPI Master mode, clock = TMR2 output/2
//	0010 = SPI Master mode, clock = FOSC/64
//	0001 = SPI Master mode, clock = FOSC/16
//	0000 = SPI Master mode, clock = FOSC/4
//	Note: Bit combinations not specifically listed here are either reserved or implemented in
//	I2C mode only.
#define SSPM_SLAVE			0b00000101
#define SSPM_SLAVE_SS 		0b00000100
#define SSPM_MASTER_TMR2	0b00000011
#define SSPM_MASTER_64		0b00000010
#define SSPM_MASTER_16		0b00000001
#define SSPM_MASTER_4		0x00
