//+--------------------------------------------------------------------------+
//|  $Workfile:: LCD.c                             $ $Revision:: 10          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 1/03/12 12:40p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/LCD.c                                    $
//+--------------------------------------------------------------------------+

#include <p18cxxx.h>
#include "qassert.h"
#include "string.h"
#include "SPI.h"
#include "LCD.h"

DEFINE_THIS_FILE;

#define CLOCK_DELAY 3	///< ms delay señales de control al LCD (err=+0/-1)

typedef enum _LcdState_t {
	LCD_IDLE,
	LCD_SEND_START,
	LCD_SENDING_TYPE,
	LCD_SENDING_DATA,
	LCD_SENDING_E1,
	LCD_SENDING_E0
} LcdState_t;

typedef enum _LcdState2_t {
	LCD_STR_IDLE,
	LCD_STR_START,
	LCD_STR_WAITING
} LcdState2_t;



// Singleton
LCD theLcd;


static uint8_t cmdTable[] = {
	INTERFACE8 | LINES2 | FONT5X7,	// Function Set: 8-bit, 2 Line, 5x7 Dots
	DISPLAY_ON | CURSOR_OFF,		// Display on Cursor off
	CLEAR,							// Clear Display (also DDRAM)
	ENTRY_RIGHT | ENTRY_NOSHIFT 	// Entry Mode Right
};

/*==========================================================================*/

LCD *LCD_ctor(	LCD *me, 
				SPI *spi,
				EventHandler onCommandCompleted) 
{
	uint8_t cmd_index = 0;
	
	me->_onCommandCompleted = onCommandCompleted;
	me->_spi = spi;
	me->_state = LCD_IDLE;
	me->_state2 = LCD_STR_IDLE;
	me->_shiftMode = NOSHIFT;
	me->_t = me->_t2 = 0;

	while (cmd_index < DIM(cmdTable)) {
		LCD_send(me, TYPE_CMD, cmdTable[cmd_index++]);
		while(LCD_isBusy(me));
	}
	
	return me;
}//


uint8_t LCD_send(LCD *me, Data_t mode, char cmd) {
	if (LCD_isBusy(me)) return 1;
	
	me->_mode = mode;
	me->_data = cmd;
	me->_state = LCD_SEND_START;
	return 0;
}//


// Display string
uint8_t LCD_sendString(LCD *me, const char *str) {

	me->_index = 0;
	me->_mode = TYPE_DATA;
	
	strncpy(me->_buff, str, LCD_BUFF_LEN);
	me->_state2 = LCD_STR_START;
	return 0;	  
}//

uint8_t LCD_sendRomString(LCD *me, char rom static far const *str) {
	if (LCD_isBusy(me)) return 1;				  // No pudo comenzarse el envío	
	
	me->_index = 0;
	me->_mode = TYPE_DATA;
	
	strncpypgm2ram(me->_buff, str, LCD_BUFF_LEN);
	me->_state2= LCD_STR_START;
	return 0;	   // indica que se comenzó el envío (NO INDICA FINALIZACION OK)
}//
			
	
void LCD_shift(LCD *me, ShiftMode_t dir, uint8_t speed, uint8_t len) {
	me->_shiftSpeed = me->_shiftTmr = speed;	
	me->_shiftLenCtr = me->_shiftLen = len;
	me->_shiftMode = dir;
}//



BOOL LCD_isBusy(LCD *me) {
	return (me->_state != LCD_IDLE);
}

/*==========================================================================*/
// 									ISR 1 ms!!
/*==========================================================================*/
// IMPORTANTE:
// Se supone DATA BUS en puerto B del MCP23S17
// Se supone CONTROL BUS en puerto A del MCP23S17:
//		GPA7: RS
//		GPA6: E
//			  R/_W  ==> CONECTADO A MASA (WRITE ONLY)
/*==========================================================================*/
void LCD_update(LCD *me) {

   /***************************************
	*                                     *
	*          T H R E A D    0           *
	*                                     *
	***************************************/
	if (me->_t) --me->_t;
	if (me->_t2) --me->_t2;
	

   /***************************************
	*                                     *
	*          T H R E A D    1           *
	*                                     *
	***************************************/
	
	/* Envía un unico caracter ubicado en me->_data */
	switch (me->_state) {
		
		case LCD_SEND_START:
			// Seleccionar registro (data/command):
			SPI_write(me->_spi, GPIOA, (me->_mode==TYPE_CMD)?0x00:0x80);
			me->_tmrDelay = CLOCK_DELAY;
			me->_state = LCD_SENDING_TYPE;
			break;
			
		case LCD_SENDING_TYPE:
			if (--me->_tmrDelay) break;						// esperar 1 a 2 ms
			
			SPI_write(me->_spi, GPIOB, me->_data);
			me->_tmrDelay = CLOCK_DELAY;
			me->_state = LCD_SENDING_DATA;
			break;
			
		case LCD_SENDING_DATA:
			if (--me->_tmrDelay) break;
			
			SPI_write(me->_spi, GPIOA, (me->_mode==TYPE_CMD)?0x40:0xC0); //E=1
			me->_tmrDelay = CLOCK_DELAY;
			me->_state = LCD_SENDING_E1;
			break;
			
		case LCD_SENDING_E1:
			if (--me->_tmrDelay) break;
				
			SPI_write(me->_spi, GPIOA, 0x00); // E=0
			me->_tmrDelay = CLOCK_DELAY;
			me->_state = LCD_SENDING_E0;
			break;
			
		case LCD_SENDING_E0:
			if (--me->_tmrDelay) break;
			
			me->_state = LCD_IDLE;
			if (me->_onCommandCompleted != null) 
				me->_onCommandCompleted();
			break;	
	}
	
	
   /***************************************
	*                                     *
	*          T H R E A D    2           *
	*                                     *
	***************************************/	
	switch(me->_state2) {
		case LCD_STR_START:
	
			// Fin del buffer?
			if (me->_index == LCD_BUFF_LEN) {
				me->_state2 = LCD_STR_IDLE;
				break;
			}

			// Fin del string?
			if (me->_buff[me->_index] == '\0') {
				me->_state2 = LCD_STR_IDLE;
				break;
			}
			
			LCD_send(me, TYPE_DATA, me->_buff[me->_index++]);
			//me->_t2 = 200;
			me->_state2 = LCD_STR_WAITING;
			break;
			
		case LCD_STR_WAITING:
			if (!LCD_isBusy(me)) {
				me->_state2 = LCD_STR_START;		       // siguiente caracter
			}
				
			break;
	}
	
			
	
	
	
	
   /***************************************
	*                                     *
	*          T H R E A D    3           *
	*                                     *
	***************************************/

	if (me->_shiftMode != NOSHIFT) {
		
		if (LCD_isBusy(me)) goto NEXT_THREAD;	// thread 1 busy
		
		if (--me->_shiftTmr) goto NEXT_THREAD;	// esperando para desplazar
		
		if (!me->_shiftLenCtr--) {	// len desplazados? return home
			me->_shiftLenCtr = me->_shiftLen;
			LCD_send(me, TYPE_CMD, HOME);
			goto NEXT_THREAD;;
		}
			
		(me->_shiftMode == RIGHT_DIR)?LCD_send(me, TYPE_CMD, SHIFT_RIGHT):
				LCD_send(me, TYPE_CMD, SHIFT_LEFT);	// desplazar
				
		me->_shiftTmr = me->_shiftSpeed;		// preset espera
	}
	
NEXT_THREAD:
	Nop();

}//

/*==========================================================================*/




