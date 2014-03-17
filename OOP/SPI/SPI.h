//+--------------------------------------------------------------------------+
//|  $Workfile:: SPI.h                             $ $Revision:: 9           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 29/02/12 3:03p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/SPI.h                                    $
//+--------------------------------------------------------------------------+
//! \file SPI.h
//! ### I/O Serial Extender MCP 23S17 (Driver).

#ifndef SPI_H_
#define SPI_H_

#include "typedefs.h"
#include "TBase.h"

/**************************************
 * Debe indicarse el módulo SPI que se * 
 * utilizará. Válido para PIC18F8722   *
 * y dispositivos de la misma flia.    *
 ***************************************/
#define  SPI_MODULE_1

/**************************************
 * Estas definiciones son de uso inter-* 
 * no de la clase y no deben ser usadas*
 * desde el programa cliente           *
 ***************************************/
#ifdef SPI_MODULE_1
	#define SSPxCON1			SSP1CON1
	#define SSPxBUF				SSP1BUF
	#define SSPxSTAT			SSP1STAT
	#define SSPxSTATbits_CKE 	SSP1STATbits.CKE
	#define PIRxbits_SSPxIF		PIR1bits.SSP1IF
	#define PIExbits_SSPIE		PIE1bits.SSP1IE
	#define TRISxbits_SDOx		TRISCbits.TRISC5
	#define TRISxbits_SCKx		TRISCbits.TRISC3
	#define TRISxbits_SSx		TRISFbits.TRISF7
#elif defined (SPI_MODULE_2)
	#define SSPxCON1			SSP2CON1
	#define SSPxBUF				SSP2BUF	
	#define SSPxSTAT			SSP2STAT
	#define SSPxSTATbits_CKE 	SSP2STATbits.CKE
	#define PIRxbits_SSPxIF		PIR3bits.SSP2IF
	#define PIExbits_SSPIE		PIE3bits.SSP2IE
	#define TRISxbits_SDOx		TRISDbits.TRISD4
	#define TRISxbits_SCKx		TRISDbits.TRISD6
	#define TRISxbits_SSx		TRISDbits.TRISD7
#else
	#error Debe definirse SPI_MODULE_1 o SPI_MODULE_2
#endif 

/** @related SPI */
typedef enum _SPI_RW {
	SPI_WRITE = 0,
	SPI_READ = 1
} SPI_RW;

/** @related SPI */
typedef enum _SendState {
	SEND_START,
	WAITING_RW,
	WAITING_REG,
	WAITING_DATA,
	SEND_IDLE
} SendState;

/*************************************************************************//** 
 * ## I/O Serial Extender MCP 23S17 (Driver). Controla uno de los módulos SPI del PIC18F8722 o dispositivos
 * compatibles cuando se conecta un expansor serial **MCP23S17**
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 ****************************************************************************/
CLASS(SPI)
	port_t 	   	   *_CS_port;
	uint8_t 		_CS_pin;
	port_t 	   	   *_RST_port;
	uint8_t 		_RST_pin;
	TBase 			_tBase;
	SPI_RW 			_r_w;
	uint8_t 		_regAddress;
	uint8_t 		_data;
	EventHandler 	_onDataSent;
	SendState		_sendState;
METHODS
	/*************************************************************************//** 
	 * Constructor. Debe indicarse los pines donde se conectan CS (Chip Select)
	 * y RST (reset) del MCP23S17 
	 * @param[in]   CS_port		Puerto donde se conecta el pin CS del MCP23S17
	 * @param[in]   CS_pin 		pin donde se conecta el CS del MCP23S17
	 * @param[in]   RST_port	Puerto donde se conecta el pin RST del MCP23S17
	 * @param[in]   RST_pin		pin donde se conecta el RST del MCP23S17	 	 	 
	 * @returns     puntero al objeto me
	 *
	 * @code        SPI_ctor(&me->_SPI1, &PORTA, 2, &PORTF, 6, onSPIdataSent);
	 * @endcode
	 * @related     SPI
	 ****************************************************************************/
	SPI *SPI_ctor(SPI* me,
					port_t *CS_port,
					uint8_t CS_pin,
					port_t *RST_port,
					uint8_t RST_pin,
					EventHandler onDataSent);

	/*************************************************************************//** 
	 * Envía un dato a un registro específico del MCP23S17.
	 * Para sacar un dato por uno de los dos puertos (A o B) debe escribirse
	 * en los registros GPIOA o GPIOB. Previamente debe configurarse el dispositivo
	 * @param[in]   reg			Registro donde será escrito/leido el dato (ver defs abajo)
	 * @param[in]   data 		Dato que será escrito en el registro indicado
	 *
	 * @code        SPI_write(&app._SPI1, GPIOA, 0x00);				 @endcode
	 * @related     SPI
	 ****************************************************************************/						
	void SPI_write(SPI* me, uint8_t reg, uint8_t data); 
	
	
	/*************************************************************************//** 
	 * Asigna un nuevo controlador de eventos para finalizacion de envío de datos
	 * @param[in]   onSpiDataSent	nuevo controlador de eventos
	 *
	 * @code        SPI_setOnSPIdataSent(me->_spi, newOnSpiDataSent);	
	 * @endcode
	 * @related     SPI
	 ****************************************************************************/						
	void SPI_setOnSPIdataSent(SPI *me, EventHandler onSpiDataSent);
	
	/*************************************************************************//** 
	 * Máquina de estados. 
	 * + Genera la secuencia correspondiente (y su temporización)
	 * para enviar un dato a un puerto del MCP23S17. 
	 * + Continúa la secuencia de escritura iniciada con SPI_write(). 
	 * + Genera el evento _onDataSent() cuando la escritura ha concluido.
	 *
	 * @code        if (PIRxbits_SSPxIF) {
	 *					SPI_update(&app._SPI1);
	 *				}				 
	 * @endcode
	 * @related     SPI
	 ****************************************************************************/							
	void SPI_update(SPI* me);
END_CLASS


/* REGISTROS DEL MCP23S17 */
#define IODIRA   	0x00
#define IODIRB   	0x01
#define IPOLA    	0x02
#define IPOLB    	0x03
#define GPINTENA 	0x04
#define GPINTENB 	0x05
#define DEFVALA  	0x06
#define DEFVALB  	0x07
#define INTCONA  	0x08
#define INTCONB  	0x09
#define IOCONA   	0x0A
#define IOCONB   	0x0B
#define GPPUA    	0x0C
#define GPPUB    	0x0D
#define INTFA    	0x0E
#define INTFB    	0x0F
#define INTCAPA  	0x010
#define INTCAPB  	0x011
#define GPIOA    	0x012
#define GPIOB    	0x013
#define OLATA    	0x014
#define OLATB    	0x015


#define WRADDR		0x40	// dirección para escritura
#define RDADDR		0x41	// dirección para lectura
#define IOCON		0x0A

#endif
