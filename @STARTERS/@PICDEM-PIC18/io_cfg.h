//;+--------------------------------------------------------------------------+
//;|       $Workfile:: io_cfg.h                   $ $Revision:: 5             $
//;+--------------------------------------------------------------------------+
//;|         $Author:: valdez                                                 $
//;|        $Modtime:: 6/02/12 2:11p                                          $
//;|        $Archive:: /@C18/SRC/Explorer1/io_cfg.h                           $
//;+--------------------------------------------------------------------------+
//;|      Module Type:                                                        $
//;|      Description:                                                        $
//;+--------------------------------------------------------------------------+


#ifndef IO_CFG_H
#define IO_CFG_H

//+----------------------------------------------------------------------------+
//| PORTA: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
										// 	11110011	
#define		AD_POT		PORTAbits.RA0	///<i Potenciometro
#define		AD_TEMP		PORTAbits.RA1	///<i Sensor Temperatura
#define		LCD_CS  	PORTAbits.RA2	///<o Chip Select LCD
#define		EEPROM_CS	PORTAbits.RA3	///<o Chip Select EEPROM
#define		AFREE4		PORTAbits.RA4	///<i	
#define		SW2			PORTAbits.RA5	///<i Tact Switch S2
#define		AFREE6		PORTAbits.RA6	///<i	
#define		AFREE7		PORTAbits.RA7	///<i	

//+----------------------------------------------------------------------------+
//| PORTB: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		SW1			PORTBbits.RB0	///<i Tact Switch S1
#define		USARTRX 	PORTBbits.RB1	///<i RS232
#define		USARTTX		PORTBbits.RB2	///<i RS232
#define		BFREE3		PORTBbits.RB3	///<i 
#define		BFREE4		PORTBbits.RB4	///<i 
#define		BFREE5		PORTBbits.RB5	///<i 
#define		ICSP1		PORTBbits.RB6	///<i icsp
#define		ICSP2		PORTBbits.RB7	///<i icsp 


//+----------------------------------------------------------------------------+
//| PORTC: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
//										//  11010111
#define		XTL1 		PORTCbits.RC0	///<i Cristal 32kHz
#define		XTL2 		PORTCbits.RC1	///<i Cristal 32kHz
#define		CFREE2		PORTCbits.RC2	///<i
#define		SCK			PORTCbits.RC3	///<o EE Serial Clock EEPROM / LCD
#define		SO  		PORTCbits.RC4	///<i EE Serial OUTPUT
#define		SI 			PORTCbits.RC5	///<o EE Serial INPUT
#define		USB1		PORTCbits.RC6	///<i USB <-> RS232
#define		USB2		PORTCbits.RC7 	///<i USB <-> RS232

//+----------------------------------------------------------------------------+
//| PORTD: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		LED0		PORTDbits.RD0	///<o LED
#define		LED1		PORTDbits.RD1	///<o LED
#define		LED2		PORTDbits.RD2	///<o LED
#define		LED3		PORTDbits.RD3	///<o LED
#define		LED4		PORTDbits.RD4	///<o LED
#define		LED5		PORTDbits.RD5	///<o LED
#define		LED6		PORTDbits.RD6	///<o LED
#define		LED7		PORTDbits.RD7	///<o LED

//+----------------------------------------------------------------------------+
//| PORTE: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		EFREE0		PORTEbits.RE0	///< 
#define		EFREE1		PORTEbits.RE1	///< 
#define		EFREE2		PORTEbits.RE2	///< 
#define		EFREE3		PORTEbits.RE3	///< 
#define		EFREE4		PORTEbits.RE4	///< 
#define		EFREE5		PORTEbits.RE5	///< 
#define		EFREE6		PORTEbits.RE6	///< 
#define		EFREE7		PORTEbits.RE7	///< 

//+----------------------------------------------------------------------------+
//| PORTF: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		FFREE0		PORTFbits.RF0	///< 
#define		FFREE1		PORTFbits.RF1	///< 
#define		FFREE2		PORTFbits.RF2	///< 
#define		FFREE3		PORTFbits.RF3	///< 
#define		FFREE4		PORTFbits.RF4	///< 
#define		FFREE5		PORTFbits.RF5	///< 
#define		LCD_RESET 	PORTFbits.RF6	///< 
#define		FFREE7		PORTFbits.RF7	///< 

//+----------------------------------------------------------------------------+
//| PORTG: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		GFREE0		PORTGbits.RG0	///< 
#define		GFREE1		PORTGbits.RG1	///< 
#define		GFREE2		PORTGbits.RG2	///< 
#define		GFREE3		PORTGbits.RG3	///< 
#define		GFREE4		PORTGbits.RG4	///< 
#define		GFREE5		PORTGbits.RG5	///< 
#define		GFREE6		PORTGbits.RG6	///< 
#define		GFREE7		PORTGbits.RG7	///< 

//+----------------------------------------------------------------------------+
//| PORTH: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		HFREE0		PORTHbits.RH0	///< 
#define		HFREE1		PORTHbits.RH1	///< 
#define		HFREE2		PORTHbits.RH2	///< 
#define		HFREE3		PORTHbits.RH3	///< 
#define		HFREE4		PORTHbits.RH4	///< 
#define		HFREE5		PORTHbits.RH5	///< 
#define		HFREE6		PORTHbits.RH6	///< 
#define		HFREE7		PORTHbits.RH7	///< 

//+----------------------------------------------------------------------------+
//| PORTJ: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		JFREE0		PORTJbits.RJ0	///< 
#define		JFREE1		PORTJbits.RJ1	///< 
#define		JFREE2		PORTJbits.RJ2	///< 
#define		JFREE3		PORTJbits.RJ3	///< 
#define		JFREE4		PORTJbits.RJ4	///< 
#define		JFREE5		PORTJbits.RJ5	///< 
#define		JFREE6		PORTJbits.RJ6	///< 
#define		JFREE7		PORTJbits.RJ7	///< 


#endif

/*
80 Pin TQFP

                                   +-----------------TX-[C6]-------------- < UART-TX
                                   | +------------------[C5]-------------- < Z6
                                   | | +----------------[C4]-------------- < Z5
                                   | | | +--------------[D3]-------------- < SPRG8(FUTURO)
                                   | | | | +------------[D2]-------------- < SPRG7
                                   | | | | | +----------[D1]-------------- < SPRG6
                                   | | | | | | +--------[D0]-------------- < SPRG5
                                   | | | | | | | +------[C3]-------------- < Z4
                                   | | | | | | | | +----[C2]-------------- < Z3
                                   | | | | | | | | | +--[C1]-------------- < Z2
                                   | | | | | | | | | | +[NC]
                                   | | | | | | | | | | | 
                                   4 4 4 4 4 3 3 3 3 3 3 
                                   4 3 2 1 0 9 8 7 6 5 4
                                  +---------------------+ 
UART-RX <>------------ [C7/RX] 1  |*                    | 33 [NC]
SPRG1   <---------------- [D4] 2  |                     | 32 [C0]-------------- < Z1   
SPRG2   <---------------- [D5] 3  |                     | 31 [A6] (LIBRE)
SPRG3   <---------------- [D6] 4  |                     | 30 [A7] (LIBRE)
SPRG4   <---------------- [D7] 5  |                     | 29 [Vss]		
                         [Vss] 6  |                     | 28 [Vdd]		
                         [Vdd] 7  |                     | 27 [E2/An7]---------- > LLAVE MANUAL
LEDS0  <------------ [B0/An12] 8  |                     | 26 [E1/An6]
LEDS1  <------------ [B1/An10] 9  |                     | 25 [E0/An5]---------- < ENABLE
LEDS2  <------------- [B2/An8] 10 |                     | 24 [A5/An4]
LEDS3  <------------- [B3/An9] 11 |                     | 23 [A4] (LIBRE)
                                  +---------------------+   
                                   1 1 1 1 1 1 1 1 2 2 2
                                   2 3 4 5 6 7 8 9 0 1 2
                                   | | | | | | | | | | | 
                                   | | | | | | | | | | +[An3] (LIBRE)
                                   | | | | | | | | | +--[An2]-------------- < V220
                                   | | | | | | | | +----[An1] (LIBRE)
                                   | | | | | | | +------[An0]-------------- < BATT
                                   | | | | | | +-MCLR---[E3] (ICD2)				
                                   | | | | | +---PGD----[B7] (ICD2)				
                                   | | | | +-----PGC----[B6] (ICD2)
                                   | | | +-------PGM----[B5] (NO UTILIZADO)
                                   | | +----------------[B4/An11]---------- < TS-1
                                   | +------------------[NC]				
                                   +--------------------[NC]	
                                   
                                   
*/
