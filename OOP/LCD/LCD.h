//+--------------------------------------------------------------------------+
//|  $Workfile:: LCD.h                             $ $Revision:: 12          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 1/03/12 12:55p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/LCD.h                                    $
//+--------------------------------------------------------------------------+
//! \file LCD.h
//!  ### Control del Display LCM-SO1602-DTR/M.
//!  http://www.8051projects.net/lcd-interfacing/basics.php
//!  Command Tables: http://www.8051projects.net/lcd-interfacing/commands.php


#ifndef LCD_H_
#define LCD_H_

#define LCD_BUFF_LEN	40		///< tamaño del buffer de escritura del LCD

#include "typedefs.h"
#include "SPI.h"

/** *Blocking* Delay - General purpose _blocking_ delayer */
#define LCD_delay(lcd, msecs)	(lcd)->_t = (msecs);  \
								while ((lcd)->_t) ClrWdt()

/** Para utilizar con la función LCD_send().
	+ El dato a enviar puede ser cualquier caracter imprimible.
	+ Los comandos a enviar se listan en las definiciones al final del archivo
	\related LCD */
typedef enum _Data_t {
	TYPE_DATA,				///< Se envía un caracter al LCD
	TYPE_CMD				///< Se envía un comando al LCD
} Data_t;

/** Para utilizar con la función LCD_shift().
	+ Usar NOSHIFT para detener el shifting de los caracteres 
	\related LCD */
typedef enum _ShiftMode_t {
	LEFT_DIR,
	RIGHT_DIR,
	NOSHIFT
} ShiftMode_t;

/*************************************************************************//** 
 * ##Control de Display Modelo _LCM SO 1602 DTR/M_.
 *
 * + Conectado a través de MCP23S17.
 * + Requiere un objeto SPI instanciado y construido **previamente en main()**.
 *
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 ****************************************************************************/
CLASS(LCD)
	uint8_t _tmrDelay;	///< temporizador para delays requeridos por el LCD
	uint8_t _t, _t2;	///< temporizadores
	SPI *_spi;			///< serial port interface (MCP23S17) para instanciar en main()
	
	uint8_t _state;		///< FSM de caracter
	uint8_t _state2;	///< FSM de string
	uint8_t _data;		///< caracter/comando a enviar
	Data_t _mode;		///< tipo de dato (caracter o comando)
	
	uint8_t _shiftLen;	///< Longitud del string a desplazar
	uint8_t _shiftLenCtr;	///< Contador de caracteres desplazados
	uint8_t _shiftSpeed;///< delay en ms entre pasos del shift
	uint8_t _shiftTmr;	///< temporizador para los efectos de display
	uint8_t _shiftMode;	///< Dirección de desplazamiento
	
	uint8_t _index;		///< índice de caracter dentro del string que se imprime
	char _buff[LCD_BUFF_LEN];	///< buffer interno
	
	EventHandler _onCommandCompleted;
	
METHODS
	/*************************************************************************//** 
	 * Constructor. Setea campos y estados iniciales. Envía comandos de inicio 
	 * 				al lcd.
	 * @param[in]   spi		puntero a SPI (MCP23S17) instanciado y construido (ctor)
	 *						desde el cliente.
	 * @param[in]   onCommandCompleted	Controlador de evento lanzado al concluir
	 *				comandos ejecutados en ISR.
	 * @note		Se supone:
	 *				+ DATA BUS en puerto B del MCP23S17, 
	 *				+ CONTROL BUS en puerto A del MCP23S17:
	 *				+ GPA7: RS
	 *				+ GPA6: E
	 *				+	  R/_W  ==> CONECTADO A MASA (WRITE ONLY)
	 * @returns     puntero al objeto.
	 *
	 * @code        LCD_ctor(&theLcd, &me->_SPI1, (EventHandler)null);   @endcode
	 * @related     LCD
	 ****************************************************************************/

	LCD *LCD_ctor(	LCD *me, 
					SPI *spi,
					EventHandler onCommandCompleted);

/*************************************************************************//** 
 * Envía un caracter (dato) o un comando al LCD.
 * @param[in]   mode  	Especifica si se trata de un dato o un comando
 * @param[in]   cmd		Dato o comando a enviar al LCD. En caso de comando,
 *						pueden usarse las definiciones en este archivo.
 * @returns     uint8_t Retorna 0 si el dato se comenzó a procesar, 1 si el LCD se encuentra
 *				ocupado y el dato no pudo ser enviado.
 *
 * @code        LCD_send(&theLcd, TYPE_CMD, CLEAR);    @endcode
 * @related     LCD
 ****************************************************************************/			
	uint8_t LCD_send(LCD *me, Data_t mode, char cmd);
	
/*************************************************************************//** 
 * Envía un string (dato) al LCD.
 * @param[in]   str  	puntero al string (RAM) que será enviado al LCD
 * @returns     uint8_t Retorna 0 si el string se comenzó a procesar, 1 si el LCD se encuentra
 *				ocupado y el string no pudo ser enviado.
 *
 * @code        LCD_sendString(&theLcd, string1);    @endcode
 * @related     LCD
 ****************************************************************************/	
	uint8_t LCD_sendString(LCD *me, const char str[]);
	
/*************************************************************************//** 
 * Envía un string desde ROM (dato) al LCD.
 * @param[in]   str  	puntero al string (FLASH ROM) que será enviado al LCD
 * @returns     uint8_t Retorna 0 si el string se comenzó a procesar, 1 si el LCD se encuentra
 *				ocupado y el string no pudo ser enviado.
 *
 * @code        LCD_sendRomString(&theLcd, msg_array[i]);    @endcode
 * @related     LCD
 ****************************************************************************/		
	uint8_t LCD_sendRomString(LCD *me, char rom static far const *str);
	
/*************************************************************************//** 
 * Rutina de actualizacion desde ISR [1ms]. Máquina de estados encargada de
 * emitir las señales de data y clock hacia el SPI correspondiente.
 * @related     LCD
 ****************************************************************************/
	void LCD_update(LCD *me);
	
/*************************************************************************//** 
 * Inicia la FSM de shifting del texto en el display. El shifting se realiza
 * desde LCD_update() en ISR. 
 * @param[in]   dir  	dirección de shifting del texto. Ver ShiftMode_t
 * @param[in]   speed  	periodo en ms de cada paso de shifting.
 * @param[in]   len  	cantidad de pasos de shift antes de enviar HOME y 
 *						recomenzar el shifting.
 *
 * @code        LCD_shift(&theLcd, RIGHT_DIR, 250, 10);   @endcode
 * @related     LCD
 ****************************************************************************/	
	void LCD_shift(LCD *me, ShiftMode_t dir, uint8_t speed, uint8_t len);
	
/*************************************************************************//** 
 * Determina si la máquina de estados se encuentra en estado IDLE.
 * @returns     BOOL Retorna TRUE si la FSM se encuentra ocupada, FALSE si se
 *				encuentra en estado IDLE.
 * @related     LCD
 ****************************************************************************/		
	BOOL LCD_isBusy(LCD *me);
	
END_CLASS

/** Sigleton para utilizar un único LCD */
extern LCD theLcd;   // SINGLETON

// CLS & CR
#define CLEAR_DISPLAY	0b00000001
#define RETURN_HOME		0b00000010

// ENTRY MODE (USAR "|")
#define ENTRY_RIGHT		0b00000110
#define ENTRY_LEFT		0b00000100
#define ENTRY_SHIFT		0b00000101
#define ENTRY_NOSHIFT	0b00000100

// DISPLAY ON/OFF - CURSOR ON/OFF/BLINK
#define DISPLAY_ON		0b00001100
#define DISPLAY_OFF		0b00001000
#define CURSOR_ON		0b00001010
#define CURSOR_OFF		0b00001000
#define BLINK_ON		0b00001001
#define BLINK_OFF		0b00001000

// CURSOR OR DISPLAY SHIFT
#define SHIFT_RIGHT		0b00011100
#define SHIFT_LEFT		0b00011000
#define CURSOR_LEFT  	0b00010000
#define CURSOR_RIGHT	0b00010100

// FUNCTION SET
#define INTERFACE4		0b00100000
#define INTERFACE8		0b00110000
#define LINES1			0b00100000
#define LINES2			0b00101000
#define FONT5X8			0b00100000
#define FONT5X7			0b00100100

// SET DDRAM/CGRAM ADDRESS
#define DDRAM_ADD(x)	0b10000000 + (x)
#define CGRAM_ADD(x)	0b01000000 + (x)



// COMANDOS RAPIDOS (combinación de los anteriores y abreviaturas)
#define CLEAR		CLEAR_DISPLAY	// CLS & return cursor home
#define HOME		RETURN_HOME		// return cursor & shifted display home DON'T CLS
#define LINE1		DDRAM_ADD(0)	// cursor a posición 0
#define LINE2		DDRAM_ADD(40)	// posición 40° (inicio segunda linea)
#define POS(x)		DDRAM_ADD(x)	// Set DDRAM address or coursor position on display
#define CGPOS(x)	CGRAM_ADD(x)	// Set CGRAM address or set pointer to CGRAM location
#define HIDE_DISPLAY 	DISPLAY_OFF + CURSOR_OFF // without clearing DDRAM content)
#define SHOW_DISPLAY	DISPLAY_ON
#define HIDE_CURSOR	DISPLAY_ON
#define SHOW_CURSOR	DISPLAY_ON + CURSOR_ON	 // CURSOR ON
#define BLINK		DISPLAY_ON + CURSOR_ON + BLINK_ON  // Display on Cursor blinking
#define NOBLINK		SHOW_CURSOR
#define DISPLAY_L 	SHIFT_LEFT // Shift entire display left
#define DISPLAY_R 	SHIFT_RIGHT // Shift entire display right
#define CURSOR_L	CURSOR_LEFT 	// Move cursor left by one character
#define CURSOR_R	CURSOR_RIGHT	// Move cursor right by one character

#define theLcd_sendCmdWait(CMD) 		LCD_send(&theLcd, TYPE_CMD, (CMD)); \
									while(LCD_isBusy(&theLcd))
									
#define theLcd_sendStrWait(STR)		LCD_sendString(&theLcd, (STR)); \
									while(LCD_isBusy(&theLcd))
									
#define theLcd_sendRomStrWait(ROMSTR)	LCD_sendRomString(&theLcd, (frchar*)(ROMSTR)); \
										while(LCD_isBusy(&theLcd))

#endif
