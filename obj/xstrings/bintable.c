//;+------------------------------------------------------------------+
//;|       $Workfile:: bintable.c                 $ $Revision:: 3     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 13/12/11 9:48p                                 $
//;|        $Archive:: /@C18/obj/xstrings/bintable.c                  $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include "xstrings.h"


void bintable(char* str_symbol, const char* str_bin, char zero, char one, char dir)
{
	// dir: 0=normal, 1=invertido
	
	char* str_bin_p = str_bin;
	char* str_sym_p = str_symbol;
	char digit;
	
	switch (dir)
	{
		case 0:		
			while (digit = *str_bin_p++) // str_bin debe ser null-terminated
			{
				if (digit == '1')
					*str_sym_p++ = one;
				else
					*str_sym_p++ = zero;
			}
			*str_sym_p = '\0';
			
			break;
			
		case 1:
			str_bin_p = str_bin + strlen(str_bin);
			
			while (str_bin_p-- != str_bin) // str_bin debe ser null-terminated
			{
				digit = *str_bin_p;
				
				if (digit == '1')
					*str_sym_p++ = one;
				else
					*str_sym_p++ = zero;
			}
			*str_sym_p = '\0';
			
			break;
			
	}
		
}//


