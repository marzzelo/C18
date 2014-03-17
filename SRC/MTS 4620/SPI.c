//+--------------------------------------------------------------------------+
//|  $Workfile:: SPI.c                             $ $Revision:: 7           $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 23/02/12 1:41p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/SPI.c                                    $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include "p18fxxx_defs.h"
#include "qassert.h"
#include "typedefs.h"
#include "SPI.h"


DEFINE_THIS_FILE;


#define TRIS_TO_PORT  18
#define LAT_TO_PORT  9


SPI *SPI_ctor(SPI* me,
				port_t *CS_port,
				uint8_t CS_pin,
				port_t *RST_port,
				uint8_t RST_pin,
				EventHandler onDataSent) 
{
	*(CS_port + TRIS_TO_PORT)  &= ~(1 << CS_pin);   // TRIS<x>bits.<CS_pin> = 0;
	*(RST_port + TRIS_TO_PORT) &= ~(1 << RST_pin); // TRIS<x>bits.<RST_pin> = 0;
	
	*RST_port &= ~(1 << RST_pin);  						     // 0: _RESET --> ON
	
	me->_CS_port = CS_port;
	me->_CS_pin = CS_pin;
	me->_RST_port = RST_port;
	me->_RST_pin = RST_pin;
	me->_onDataSent = onDataSent;
	
	
	SSPxSTAT = SMP_MID | TRM_ACT_IDLE;
	SSPxCON1 = SSP_ENABLE | CKP_IDLEISLO | SSPM_MASTER_16;

	TRISxbits_SDOx = 0;			// data output 
	TRISxbits_SCKx = 0;			// clock drive (MASTER MODE)
	TRISxbits_SSx = 1;			
	PIRxbits_SSPxIF = 0;		// borrar flag de interrupción	

	me->_sendState = SEND_IDLE;
		
	*RST_port |= (1 << RST_pin);  							// 1: _RESET --> OFF
	
	PIExbits_SSPIE = 1;								 // enable interrupt request		
	
}//
				


void SPI_write(SPI* me, uint8_t reg, uint8_t data) 
{
	me->_r_w = WRADDR;  // escritura
	me->_regAddress = reg;
	me->_data = data;
	
	// LATAbits.LATA2 = 0;			
	*(me->_CS_port) &= ~(1 << me->_CS_pin); 			   // CHIP SELECT --> ON
	SSPxBUF = WRADDR;
	me->_sendState = WAITING_RW;

}//

void SPI_setOnSPIdataSent(SPI *me, EventHandler newOnSpiDataSent) 
{
	me->_onDataSent = newOnSpiDataSent;
}//


// COLOCAR EN SPI-ISR
void SPI_update(SPI* me) 
{
	switch ((uint8_t)me->_sendState) {
		
		case WAITING_RW:
			//Nop();
			SSPxBUF = me->_regAddress;
			me->_sendState = WAITING_REG;
			break;
			
		case WAITING_REG:
			//Nop();
			SSPxBUF = me->_data;
			me->_sendState = WAITING_DATA;
			break;
			
		case WAITING_DATA:
			//LATAbits.LATA2 = 1 --> CHIP DE-SELECT:
			*(me->_CS_port) |= (1 << me->_CS_pin);	
			if (me->_onDataSent != null) me->_onDataSent();
			me->_sendState = SEND_IDLE;
			break;
	}
}//


	
	

					



					
