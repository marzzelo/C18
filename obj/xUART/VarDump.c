
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>
#include <xusart.h>		// Macros BusyUART() y putcUART()

void VarDump(char Var, rom char* Title){
	putrsUART(Title);
	putsUART(Hex2Str(Var, 2));
	putcUART('\n');
}//

