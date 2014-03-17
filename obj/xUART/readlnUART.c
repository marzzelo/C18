
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>
#include "xusart.h"		// Macros BusyUART() y putcUART()

void readlnUART(char* s1, const char MaxLen)
	{
	char* ps1 = s1;
	char i = 0;
	while (((*ps1++ = getcharUART()) != '\n') && (++i < MaxLen)) putsUART(s1);
	*--ps1 = 0x00;	//EOL
	}//

