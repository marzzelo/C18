
// Written By: Marcelo Valdéz, DOBA Embedded Systems

#include <p18cxxx.h>
#include <xusart.h>		// Macros BusyUART() y putcUART()

//+--------------------------------------------------------+
//|  char* Hex4Str(int HexDigit)                           |
//+--------------------------------------------------------+
//|  Convierte un uint (16 bits) en string.                |
//|  Coloca un espacio al final del string.                |
//|  Llena con 0 a la izquierda si es necesario.           |
//+--------------------------------------------------------+
//|    char* s;                                            |
//|    s = Hex4Str(0xFA5C);                                |
//|    putsUART(s);                                        |
//+--------------------------------------------------------+
char* Hex2Str(int HexDigit, int Pos) {
	int k = HexDigit;
	int i, j;
	char Output[] = {0,0,0,0,0};
	
	for (j=0; j<Pos; j++) {
		i = k & 0x000F;
		Output[Pos-1-j] = (i <= 9) ? (i + 0x30) : (i + 0x37);
		k = k >> 4;
	}

    return Output;
}//

