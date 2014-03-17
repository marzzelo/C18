//;+--------------------------------------------------------------------------+
//;|       $Workfile:: io_cfg.h                   $ $Revision:: 2             $
//;+--------------------------------------------------------------------------+
//;|         $Author:: Mav                                                    $
//;|        $Modtime:: 16/06/11 8:40p                                         $
//;|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/io_cfg.h     $
//;+--------------------------------------------------------------------------+
//;|      Module Type:                                                        $
//;|      Description:                                                        $
//;+--------------------------------------------------------------------------+


#ifndef IO_CFG_H
#define IO_CFG_H

//+----------------------------------------------------------------------------+
//| PORTA: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
	
#define		BATT	PORTAbits.RA0	///< Nivel de Batería (ANALOG)
#define		Z7		PORTAbits.RA1	///< ZONA 7
#define		Z8  	PORTAbits.RA2	///< ZONA 8
#define		V220	PORTAbits.RA3	///< Comunicación módulos auxiliares CLOCK
#define		SER_DT	PORTAbits.RA4	///< Comunicación módulos auxiliares DATA
#define		SER_EN	PORTAbits.RA5	///< HABILITACION MODULO AUXILIAR
#define		FREE2	PORTAbits.RA6	
#define		FREE3	PORTAbits.RA7	

//+----------------------------------------------------------------------------+
//| PORTB: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
/* Los pines dedicados al control del array de leds se reconfiguran permanentemente
	durante la ejecución del programa para generar el barrido, mediante la rutina LedUpdate()
	en ISR  */

#define		TS1		PORTBbits.RB4	///< I Tact Switch principal (paráms fábrica)
#define		BUZZ	PORTBbits.RB5
#define 	TRS1	TRISBbits.TRISB4

//+----------------------------------------------------------------------------+
//| PORTC: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
/* El puerto C está dedicado a los sensores de entrada (zonas) y a la comunicacion
	serial con el modem GSM */
	
#define		Z0	 	PORTCbits.RC0	
#define		Z1	 	PORTCbits.RC1
#define		Z2 		PORTCbits.RC2
#define		Z3 		PORTCbits.RC3
#define		Z4  	PORTCbits.RC4
#define		Z5 		PORTCbits.RC5
//					PORTCbits.RC6 	<- UART TX
//					PORTCbits.RC7 	<- UART RX

//+----------------------------------------------------------------------------+
//| PORTD: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		SPRG4	PORTDbits.RD0	///< Salida programable Nº 5 
#define		SPRG5	PORTDbits.RD1	///< Salida programable Nº 6 
#define		SPRG6	PORTDbits.RD2	///< Salida programable Nº 7 
#define		SPRG7	PORTDbits.RD3	///< Futura salida Nº 8
#define		SPRG0	PORTDbits.RD4	///< Salida programable Nº 1
#define		SPRG1	PORTDbits.RD5	///< Salida programable Nº 2
#define		SPRG2	PORTDbits.RD6	///< Salida programable Nº 3
#define		SPRG3	PORTDbits.RD7	///< Salida programable Nº 4

//+----------------------------------------------------------------------------+
//| PORTE: Definiciones de pines                                               |
//+----------------------------------------------------------------------------+
#define		RING_IN		PORTEbits.RE0	///< RING SIGNAL FROM MODEM
#define		TOE			PORTEbits.RE1	///< Habilita Lectura DTMF (Tri-state Output Enable)(OUTPUT)
#define		LLAVE		PORTEbits.RE2	///< Llave de activación manual
// RE3 = MCLR#


#endif

/*
44 Pin TQFP

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
