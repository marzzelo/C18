#include <p18cxxx.h>					
#include <string.h>
#include "flash.h"


static void wrSequence(void); // Secuencia de escritura o borrado de Flash

#pragma code
/**************************************************************************//** 
* @Descripcion	escribe en FLASH un bloque de 64 bytes de datos desde RAM					
* @param[in]	address  Dirección base en la memoria de programa (FLASH)
*						 donde se escribiran los datos.
* @param[in]	*buffer	 Puntero a un buffer en RAM conteniendo los datos
* @test
* @code			FFwrite(0x7C00, myData);                             @endcode
*
* $Author: Mav $ $Revision: 14 $ $Date: 4/12/10 2:15p $ 			
*******************************************************************************/
#if (defined(__18F4520) || defined(__18F452))

char FFwrite(unsigned long address, const unsigned char *buffer)
{
	char i;
	char tries = 3;

	unsigned int mAddress = address; // para verificar
	unsigned char* mBuffer = buffer;
			
	while (tries)
	{
		ClrWdt();
		TBLPTR = address;
		EECON1bits.FREE = 1; // BORRAR bloque de 64 bytes
		wrSequence(); // Iniciar borrado
		
		TBLPTR = address - 32;
		for(i=0; i<32; i++) 
		{
			TABLAT = buffer[i];
			_asm
			TBLWTPOSTINC
			_endasm
		}
		
		EECON1bits.FREE = 0; // ESCRIBIR datos (Buffer interno de 32 bytes)
		wrSequence(); // Iniciar escritura
		
		TBLPTR = address;
		for(i=32; i<64; i++) 
		{
			TABLAT = buffer[i];
			_asm
			TBLWTPOSTINC
			_endasm
		}
	
		EECON1bits.FREE = 0; // ESCRIBIR datos (Buffer interno de 32 bytes)
		wrSequence(); // Iniciar escritura
		
		i = memcmppgm2ram((void*)buffer, (far rom void*)address, 64);
		if (i == 0)
			return 0; // Escritura OK
	} 
	
	return i; // Error de escritura en FLASH
}//


#elif (defined(__18F4620) || defined(__18F4685))

char FFwrite(unsigned long address, const unsigned char *buffer)
{
	char i;
	char tries = 3;

	unsigned int mAddress = address; // para verificar
	unsigned char* mBuffer = buffer;
			
	while (tries)
	{
		ClrWdt();
		TBLPTR = address;
		EECON1bits.FREE = 1; // BORRAR bloque de 64 bytes
		wrSequence(); // Iniciar borrado
		
		TBLPTR = address - 64;
		for(i=0; i<64; i++) 
		{
			TABLAT = buffer[i];
			_asm
			TBLWTPOSTINC
			_endasm
		}
		
		EECON1bits.FREE = 0; // ESCRIBIR datos (Buffer interno de 32 bytes)
		wrSequence(); // Iniciar escritura
		
		
		// VERIFICACIÓN DE ESCRITURA
		i = memcmppgm2ram((void*)buffer, (far rom void*)address, 64);
		if (i == 0)
			return 0; // Escritura OK
	} 
	
	return i; // Error de escritura en FLASH
}//


#endif





// común a todos los procesadores:
void wrSequence()
{
	unsigned char XINTCON = INTCON;
	
	EECON1bits.EEPGD = 1;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	INTCON = XINTCON;						  /* Por si GIE = 0 desde antes */
	
	EECON1bits.WREN = 0;	
}//


