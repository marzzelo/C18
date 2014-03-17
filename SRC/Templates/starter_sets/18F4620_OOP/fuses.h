/*********************************************************************
 *              PIC 18F4520 CONFIGURATION PRAGMAS - MAV              *
 *********************************************************************/
#define	CPONOFF ON							// Code Protection Blocks

#pragma config 	OSC 	= INTIO67			// Oscilator mode
#pragma config 	FCMEN 	= OFF				// Fail-Safe Clock Monitor disabled
#pragma config 	IESO 	= OFF				// Oscillator Switchover mode disabled
#pragma config 	PWRT 	= ON				// Power On Timer 
#pragma config 	BOREN 	= ON 				// Brown-out Reset disabled in hardware and software
#pragma config 	BORV 	= 0 				// Brown-out Reset VOLTAGE
#pragma config 	WDT 	= ON				// Watch Dog Timer 
#pragma config 	WDTPS 	= 512				// WDT Postscaler

#pragma config 	MCLRE 	= ON 				// RE3 input pin enabled; MCLR disabled
#pragma config 	LPT1OSC = OFF 				// Timer1 configured for higher power operation
#pragma config 	PBADEN 	= OFF 				// PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config 	CCP2MX 	= PORTBE 			// CCP2 input/output is multiplexed with RB3

#pragma config 	STVREN 	= ON				// Stack Overflow Reset
#pragma config 	LVP 	= OFF				// Low Voltage ICSP
#pragma config 	DEBUG 	= OFF				// Background debugger enabled, RB6 and RB7 are dedicated 
#pragma config 	XINST 	= OFF          		// Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
	
	
#pragma config 	CP0 	= CPONOFF			// Block 0 (000800-001FFFh) code-protected 
#pragma config	CP1 	= CPONOFF 			// Block 1 (002000-003FFFh) code-protected 
#pragma config	CP2 	= CPONOFF 			// Block 2 (004000-005FFFh) code-protected 
#pragma config	CP3 	= CPONOFF			// Block 3 (006000-007FFFh) code-protected 

#pragma config 	CPB 	= CPONOFF			// Boot block (000000-0007FFh) code-protected 
#pragma config 	CPD 	= OFF				// Data EEPROM code-protected 

#pragma config 	WRT0 	= OFF	 			// Block 0 (000800-001FFFh) write-protected  
#pragma config 	WRT1 	= OFF 				// Block 1 (002000-003FFFh) write-protected  
#pragma config 	WRT2 	= OFF 				// Block 2 (004000-005FFFh) write-protected  
#pragma config 	WRT3 	= OFF 				// Block 3 (006000-007FFFh) write-protected  

#pragma config 	WRTB 	= OFF 				// Boot block (000000-0007FFh) write-protected  
#pragma config 	WRTC 	= OFF 				// Configuration registers (300000-3000FFh) write-protected  
#pragma config 	WRTD 	= OFF 				// Data EEPROM write-protected  

#pragma config 	EBTR0 	= OFF 				// Block 0 (000800-001FFFh) not protected from table reads executed in other blocks  
#pragma config 	EBTR1 	= OFF 				// Block 1
#pragma config 	EBTR2 	= OFF 				// Block 2
#pragma config 	EBTR3 	= OFF 				// Block 3

#pragma config 	EBTRB 	= OFF 				// Block 0-7FF
