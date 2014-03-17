#include <p18cxxx.h>		
#include "eeprom.h"

#pragma code
/**************************************************************************//** 
* Descripción:	

The data EEPROM is a high-endurance, byte-addressable
array that has been optimized for the storage of
frequently changing information (e.g., program
variables or other data that are updated often).
Frequently changing values will typically be updated
more often than specification D124. If this is not the
case, an array refresh must be performed. For this
reason, variables that change infrequently (such as
constants, IDs, calibration, etc.) should be stored in
Flash program memory.

A simple data EEPROM refresh routine is shown in
Example 6-3.				

*******************************************************************************
* $Author: Mav $ $Revision: 2 $ $Date: 4/12/10 2:49p $ 			
*******************************************************************************/
#if (defined(__18F4620) || defined(__18F4685))
void EErefresh()
{
	unsigned char p, a, v;
	for (p=0; p<4;p++)
	{
		for (a=0; a < 256; a++)
		{
			v = EEread(p, a);
			EEwrite(p, a, v);
		}
	}
}
#endif
//	
