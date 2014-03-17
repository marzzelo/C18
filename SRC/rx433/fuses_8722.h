//+--------------------------------------------------------------------------+
//|  $Workfile:: fuses_8722.h                        $ $Revision:: 6         $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 10/02/12 12:14p                                              $
//|  $Archive:: /@C18/SRC/Explorer1/fuses_8722.h                             $
//+--------------------------------------------------------------------------+

/*********************************************************************
 *              PIC 18F8722 CONFIGURATION PRAGMAS - MAV              *
 *********************************************************************/
#define	CPONOFF OFF							// Code Protection Blocks 

#pragma config 	OSC 	= INTIO67			// Oscilator mode
#pragma config 	FCMEN 	= OFF				// Fail-Safe Clock Monitor disabled
#pragma config 	IESO 	= OFF				// Oscillator Switchover mode disabled
#pragma config 	PWRT 	= OFF				// Power On Timer 
#pragma config 	BOREN 	= OFF 				// Brown-out Reset disabled in hardware and software
#pragma config 	BORV 	= 0 				// Brown-out Reset VOLTAGE
#pragma config 	WDT 	= OFF				// Watch Dog Timer 
#pragma config 	WDTPS 	= 512				// WDT Postscaler

#pragma config 	MODE	= MC				// Processor Data Memory Mode Select bits:
//#pragma config 	ADDRBW	= ADDR20BIT		// Address Bus Width Select bits
//#pragma config 	DATABW	= ADDR16BIT		// Data Bus Width Select bit
//#pragma config 	WAIT	= ON			// External Bus Data Wait Enable bit

#pragma config 	CCP2MX 	= PORTBE 			// CCP2 MUX bit
#pragma config 	ECCPMX 	= PORTH 			// ECCP MUX bit
#pragma config 	LPT1OSC = OFF 				// Low-Power Timer1 Oscillator Enable bit
#pragma config 	MCLRE 	= ON 				// RE3 input pin enabled; MCLR disabled
#pragma config 	STVREN 	= ON 				// Stack Full/Underflow Reset Enable bit

#pragma config 	LVP 	= OFF				// Low Voltage ICSP
#pragma config 	BBSIZ 	= BB2K				// Boot Block Size Select bits
#pragma config 	XINST 	= OFF          		// Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config 	DEBUG 	= OFF				// Background debugger enabled, RB6 and RB7 are dedicated 
	
	
#pragma config 	CP0 	= CPONOFF			// Block 0 (000800-001FFFh) code-protected 
#pragma config	CP1 	= CPONOFF 			// Block 1 (002000-003FFFh) code-protected 
#pragma config	CP2 	= CPONOFF 			// Block 2 (004000-005FFFh) code-protected 
#pragma config	CP3 	= CPONOFF			// Block 3 (006000-007FFFh) code-protected 
#pragma config 	CP4 	= CPONOFF			// Block 4 (008000-009FFFh) code-protected 
#pragma config	CP5 	= CPONOFF 			// Block 5 (00A000-00BFFFh) code-protected 
#pragma config	CP6 	= CPONOFF 			// Block 6 (00C000-00CFFFh) code-protected 
#pragma config	CP7 	= CPONOFF			// Block 7 (00E000-00FFFFh) code-protected 

#pragma config 	CPB 	= CPONOFF			// Boot block (000000-0007FFh) code-protected 
#pragma config 	CPD 	= OFF				// Data EEPROM code-protected 

#pragma config 	WRT0 	= OFF	 			// Block 0 (000800-001FFFh) write-protected  
#pragma config 	WRT1 	= OFF 				// Block 1 (002000-003FFFh) write-protected  
#pragma config 	WRT2 	= OFF 				// Block 2 (004000-005FFFh) write-protected  
#pragma config 	WRT3 	= OFF 				// Block 3 (006000-007FFFh) write-protected  
#pragma config 	WRT4 	= OFF	 			// Block 4 (008000-009FFFh) write-protected  
#pragma config 	WRT5 	= OFF 				// Block 5 (00A000-00BFFFh) write-protected  
#pragma config 	WRT6 	= OFF 				// Block 6 (00C000-00DFFFh) write-protected  
#pragma config 	WRT7 	= OFF 				// Block 7 (00E000-00FFFFh) write-protected  

#pragma config 	WRTB 	= OFF 				// Boot block (000000-0007FFh) write-protected  
#pragma config 	WRTC 	= OFF 				// Configuration registers (300000-3000FFh) write-protected  
#pragma config 	WRTD 	= OFF 				// Data EEPROM write-protected  

#pragma config 	EBTR0 	= OFF 				// Block 0 (000800-001FFFh) not protected from table reads executed in other blocks  
#pragma config 	EBTR1 	= OFF 				// Block 1
#pragma config 	EBTR2 	= OFF 				// Block 2
#pragma config 	EBTR3 	= OFF 				// Block 3
#pragma config 	EBTR4 	= OFF 				// Block 4
#pragma config 	EBTR5 	= OFF 				// Block 5
#pragma config 	EBTR6 	= OFF 				// Block 6
#pragma config 	EBTR7 	= OFF 				// Block 7

#pragma config 	EBTRB 	= OFF 				// Block 0-7FFF
