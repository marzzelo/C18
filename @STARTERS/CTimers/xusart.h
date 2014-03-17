/***********************************************************************
 *         $Workfile:: xusart.h                   $ $Revision:: 2     $*
 *           $Author:: Marcelo                                        $*
 *          $Modtime:: 11/08/10 3:43p                                 $*
 *          $Archive:: /@CODE/SRC/GSM4620_STD/xusart.h                $*
 ***********************************************************************/

#ifndef XUSART_H
#define XUSART_H 

/// Inserta un caracter en el puerto serial.
char putcUART(const ram char data);	

/// Envia un string \b ram por el puerto serial	
char* xputsUART(const ram char* data);	

/// Envia un string \b rom por el puerto serial
rom char* putrsUART(const rom char* data);	

/// Recibe un string desde el puerto serial
char* getsUART(char *buffer, const unsigned char len);	

/// Reinicia la logica de recepcion del puerto serial
void FlushUART(void);				

/// Recibe un caracter desde el puerto serial. NO retorna hasta no recibir el byte!
char getcharUART(void);					

/// Escribe un caracter en la UART luego de verificar que no se encuentre transmitiendo
char putcharUART(char a);

/// Recibe caracteres hasta encontrar un RC
void readlnUART(char* s1, const char MaxLen); 

/// Recibe n caracteres
char* getnUART(char *buffer, int len);

///< gets UART status (1 = TSR empty | 0 = TSR full)
#define BusyUART()			!TXSTAbits.TRMT		

///< devuelve \b 1 si hay un caracter esperando en el puerto
#define DataRdyUSART()		PIR1bits.RCIF		

///< gets a byte from USART
#define getcUART()			RCREG		
    	
///< envia un retorno de linea al puerto
#define	LineFeed()			putcUART('\n')		

///< Para resetear la lógica de recepción por cualquier problema:
#define ResetUART()						RCSTAbits.CREN = 0; RCSTAbits.CREN = 1

///< Macro para evitar el casting (rom char*)
#define Print( x )						putrsUART((rom char*)( x )) \	
					
					
					
					

//////////////////////////////////////////////////////////////////////////////////					
//                               D E P R E C A T E D 							//
//////////////////////////////////////////////////////////////////////////////////

//      SETEAR REGISTROS EN FORMA MANUAL - VER ARCHIVOS P18FXXX_DEFS.h          //

/** 
TXSTA SFR:  8-bit & TXenable & AsynchMode(SYNC=0) & HighSpeed(BRGH=1)
@warning 	ESTE REGISTRO SE SETEA AUTOMATICAMENTE SI SE UTILIZA EL VDI DE MICROCHIP **/
#define UART_TXON			0b10100100				

/** 
USARTenable & 8-bit & RXenable
@warning ESTE REGISTRO SE SETEA AUTOMATICAMENTE SI SE UTILIZA EL VDI DE MICROCHIP 
RCSTA SFR **/
#define UART_RXON			0b10010000				

/** 
@warning ESTE REGISTRO SE SETEA AUTOMATICAMENTE SI SE UTILIZA EL VDI DE MICROCHIP 
BAUDCON SFR **/
#define UART_BRG16			0b00001000				///< 16-bit BaudRate Generator(BRG16=1) & All-Direct & !wikeup & !ABD

// Ejemplo:
// 		TXSTA = UART_TXON;
// 		RCSTA = UART_RXON;
// 		BAUDCON = UART_BRG16;

/** 
Calcula el BaudRate 
@warning EL BAUDRATE SE SETEA AUTOMATICAMENTE SI SE UTILIZA EL VDI DE MICROCHIP **/
#define SetBaudRate( BRATE, FOSC )		BAUDCON = UART_BRG16; \
										SPBRG = (FOSC) * 250000 / ((BRATE) + 1); \
										SPBRGH = ((FOSC) * 250000 / ((BRATE) + 1)) >> 8	


#endif										
