//;+------------------------------------------------------------------+
//;|       $Workfile:: p18f4620_defs.h            $ $Revision:: 6     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 22/11/10 8:51p                                 $
//;|        $Archive:: /@CODE/SRC/GSM4620_STD/p18f4620_defs.h         $
//;+------------------------------------------------------------------+

/* PIC 18F4620 - Definiciones para carga directa de registros */


/************************************************************/	
/*															*/
/*    Oscilator Control - Marcelo A. Valdéz - Sept 2008     */		
/*															*/
/************************************************************/	
// para OSCCON

// A. Comportamiento frente a SLEEP
#define IDLE_ON_SLEEP 		0b11111111      // Device enters Idle mode on SLEEP instruction
#define SLEEP_ON_SLEEP 		0b01111111		// Device enters Sleep mode on SLEEP instruction

// B. Clock source Select
#define CLK_INT				0b11111111		// Internal oscillator (Ver opciones C)
#define CLK_TMR1			0b11111101		// Timer1 oscillator
#define CLK_OSC				0b11111100		// Primary oscillator

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

/************************************************************/	
/*															*/
/*      Timer0 Control - Marcelo A. Valdéz - June 2006      */
/*															*/
/************************************************************/	
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




/************************************************************/	
/*															*/
/*      Timer1 Control - Marcelo A. Valdéz                  */
/*															*/
/************************************************************/	
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

/************************************************************/	
/*															*/
/*			    INTCON: INTERRUPT CONTROL REGISTER			*/
/*															*/
/************************************************************/	
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

//bit 2 TMR0IF: TMR0 Overflow Interrupt Flag bit
//1 = TMR0 register has overflowed (must be cleared in software)
//0 = TMR0 register did not overflow

/*(N/A)*/

//bit 1 INT0IF: INT0 External Interrupt Flag bit
//1 = The INT0 external interrupt occurred (must be cleared in software)
//0 = The INT0 external interrupt did not occur

/*(N/A)*/

//bit 0 RBIF: RB Port Change Interrupt Flag bit(1)
//1 = At least one of the RB7:RB4 pins changed state (must be cleared in software)
//0 = None of the RB7:RB4 pins have changed state

/*(N/A)*/

//Note 1: A mismatch condition will continue to set this bit. Reading PORTB will end the mismatch condition and
//allow the bit to be cleared.


/************************************************************/	
/*															*/
/*       RCSTA: RECEIVE STATUS AND CONTROL REGISTER         */
/*															*/
/************************************************************/	
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


/************************************************************/	
/*															*/
/*       TXSTA: TRANSMIT STATUS AND CONTROL REGISTER        */
/*															*/
/************************************************************/	
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


/************************************************************/	
/*															*/
/*                  P  I  E  1  -  INTERRUPT ENABLE         */
/*															*/
/************************************************************/	
// IMPORTANTE:  USAR EL OPERADOR "OR" PARA SELECCIONAR ESTOS BITS!!

//bit 7 SPPIE: Streaming Parallel Port Read/Write Interrupt Enable bit(1)
//1 = Enables the SPP read/write interrupt
//0 = Disables the SPP read/write interrupt
#define SPPIE_ON			0b10000000
#define SPPIE_OFF			0x00

//bit 6 ADIE: A/D Converter Interrupt Enable bit
//1 = Enables the A/D interrupt
//0 = Disables the A/D interrupt
#define ADIE_ON				0b01000000
#define ADIE_OFF			0x00

//bit 5 RCIE: EUSART Receive Interrupt Enable bit
//1 = Enables the EUSART receive interrupt
//0 = Disables the EUSART receive interrupt
#define EUSART_RX_ON		0b00100000
#define EUSART_RX_OFF		0x00

//bit 4 TXIE: EUSART Transmit Interrupt Enable bit
//1 = Enables the EUSART transmit interrupt
//0 = Disables the EUSART transmit interrupt
#define EUSART_TX_ON		0b00010000
#define EUSART_TX_OFF		0x00

//bit 3 SSPIE: Master Synchronous Serial Port Interrupt Enable bit
//1 = Enables the MSSP interrupt
//0 = Disables the MSSP interrupt
#define SSPIE_ON			0b00001000
#define SSPIE_OFF			0x00

//bit 2 CCP1IE: CCP1 Interrupt Enable bit
//1 = Enables the CCP1 interrupt
//0 = Disables the CCP1 interrupt
#define CCP1IE_ON			0b00000100
#define CCP1IE_OFF			0x00

//bit 1 TMR2IE: TMR2 to PR2 Match Interrupt Enable bit
//1 = Enables the TMR2 to PR2 match interrupt
//0 = Disables the TMR2 to PR2 match interrupt
#define TMR2IE_ON			0b00000010
#define TMR2IE_OFF			0x00

//bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit
//1 = Enables the TMR1 overflow interrupt
//0 = Disables the TMR1 overflow interrupt
#define TMR1IE_ON			0b00000001
#define TMR1IE_OFF			0x00




/************************************************************/	
/*															*/
/*        ADCON0 - Marcelo A. Valdéz - June 2006            */
/*															*/
/************************************************************/	

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



/************************************************************/	
/*															*/
/*        ADCON1 - Marcelo A. Valdéz - June 2006            */
/*															*/
/************************************************************/	
//bit 7-6 Unimplemented: Read as '0'

//bit 5 	VCFG1: 			Voltage Reference Configuration bit (VREF- source)
//1 = VREF- (AN2)
//0 = VSS
#define VCFG1_AN2			0xFF
#define VCFG1_VSS			0b11011111

//bit 4 	VCFG0: 			Voltage Reference Configuration bit (VREF+ source)
//1 = VREF+ (AN3)
//0 = VDD
#define VCFG0_AN3			0xFF
#define VCFG0_VDD			0b11101111

//bit 3-0 	PCFG3:PCFG0: 	A/D Port Configuration Control bits:	
#define A12_D0				0b11110000			
#define A11_D1				0b11110011			
#define A10_D2				0b11110100			
#define A9_D3				0b11110101			
#define A8_D4				0b11110110			
#define A7_D5				0b11111000			
#define A6_D6				0b11111001			
#define A5_D7				0b11111010			
#define A4_D8				0b11111011			
#define A3_D9				0b11111100			
#define A2_D10				0b11111101			
#define A1_D11				0b11111110			
#define A0_D12				0x0F



/************************************************************/	
/*															*/
/*        ADCON2 - Marcelo A. Valdéz -				        */
/*															*/
/************************************************************/	

//bit 7 ADFM: A/D Result Format Select bit
//1 = Right justified
//0 = Left justified
#define AD_RIGHT			0xFF				// Right justified
#define AD_LEFT				0b01111111			// Left justified

//bit 6 Unimplemented: Read as '0'

//bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits
//111 = 20 TAD
//110 = 16 TAD
//101 = 12 TAD
//100 = 8 TAD
//011 = 6 TAD
//010 = 4 TAD
//001 = 2 TAD
//000 = 0 TAD(1)
#define ACQT_20					0xFF			
#define ACQT_16					0b11110111		
#define ACQT_12					0b11101111		
#define ACQT_8 					0b11100111		
#define ACQT_6 					0b11011111		
#define ACQT_4 					0b11010111		
#define ACQT_2 					0b11001111		
#define ACQT_0 					0b11000111		


//bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits
//111 = FRC (clock derived from A/D RC oscillator)(1)
//110 = FOSC/64
//101 = FOSC/16
//100 = FOSC/4
//011 = FRC (clock derived from A/D RC oscillator)(1) (repetido, no se define)
//010 = FOSC/32
//001 = FOSC/8
//000 = FOSC/2
#define ADCS_FRC				0xFF			// FRC (clock derived from A/D RC oscillator)
#define ADCS_64					0b11111110		// Conv Clock =  2·TOSC
#define ADCS_16					0b11111101		// Conv Clock =  4·TOSC
#define ADCS_32					0b11111100		// Conv Clock =  8·TOSC
#define ADCS_8 					0b11111010		// Conv Clock = 32·TOSC
#define ADCS_2 					0b11111000		// Conv Clock = 64·TOSC


