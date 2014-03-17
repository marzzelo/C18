
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>
#include "xusart.h"		// Macros BusyUART() y putcUART()

/**********************************************************************
*    Function Name:  DumpRam                                          *
*    Return Value:   void                                             *
*    Parameters:     StartPos: puntero a la posición inicial de 	  *
*					 memoria RAM a volcar.							  *
*					 DumpLength: Cantidad de bytes a volcar			  *			
*    Description:    This routine vuelca posiciones de memoria RAM    *
*                    en el formato: 0418:  [00,00,00,00,00,00,00,00]  *
*	 Example:	 	 												  *
*					 char s[] = "12345";					 		  *
*					 DumpRam(s, 5); 								  *
*	 Output:														  *
*					 0301: [31,32,33,34,35]							  *
**********************************************************************/
void DumpRam(char* StartPos, int DumpLength) {
	int i;
	char* rampos = StartPos;	// apuntar a la posición inicial
	
	putsUART(Hex2Str((int)rampos, 4));
	putrsUART((rom char*)":  [");		
	
	for (i=0; i<DumpLength; i++) {
		putsUART(Hex2Str(*rampos++, 2));
		putcUART(',');
	}

	putrsUART((rom char*)"]\n");
}//

