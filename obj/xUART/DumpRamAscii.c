
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>
#include "xusart.h"		// Macros BusyUART() y putcUART()

void DumpRamAscii(char* StartPos, int DumpLength) {
	int i;
	char* rampos = StartPos;	// apuntar a la posición inicial
	
	putsUART(Hex2Str((int)rampos, 4));
	putrsUART((rom char*)":  [");		
	
	for (i=0; i<DumpLength; i++) {
		putcUART(*rampos++);
	}

	putrsUART((rom char*)"]\n");
}//


