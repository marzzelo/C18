//;+------------------------------------------------------------------+
//;|       $Workfile:: xstrings.c                 $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 12/11/08 1:39p                                 $
//;|        $Archive:: /@CODE/obj/xstring/xstrings.c                  $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>


/*****************************************************************//** 
$Revision: 1 $  <hr>
@Descripcion 	Inserta un string dentro de otro en el lugar 
				indicado por el signo chr_key

@param[in]		str_dest	buffer de salida del string resultante
@param[in]		str_src		string origen
@param[in]		str_rep		String a insertar
@param[in]		chr_key		caracter indicador de posición de inserción

<hr>
******************************************************************* **/ 
 void strinsert(char* str_dest, const char* str_source, const char* str_rep)
 {
	 int len1 = strcspnrampgm(str_source, (far rom char*)"*#$");
	 int len_source = strlen(str_source);
	 
	 strncpy(str_dest, str_source, len1);
	 str_dest[len1] = '\0';
	 
	 strcat(str_dest, str_rep);
	 if (len1 == len_source) 
	 {
		 str_dest[len1] = '\0';
		 return;
	 }
	 
	 strcat(str_dest, &str_source[len1+1]);
}//

/*****************************************************************//** 
$Revision: 1 $  <hr>
@Descripcion 	Extrae un substring encapsulado con "" dentro
				de otro string.

@param[in]		str_dest	buffer de salida del string extraido
@param[in]		str_src		string donde se encuentra el encapsulado

<hr>
******************************************************************* **/ 
void strextract(char* str_dest, char* str_source)
{
	static const far rom char quotation[] = "\"";
	
	char* pos = strtokpgmram(str_source, quotation);
	if ((pos = strtokpgmram(NULL, quotation)) == NULL)
		str_dest[0] = '\0';
	else
		strcpy(str_dest, pos);
		
}//
	 
	 


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



void padl(char* str_topad, char padchar, unsigned char numchars)
{
	char i;
	
	
	for (i = strlen(str_topad); i >= 0; i--)
		str_topad[i+numchars] = str_topad[i];

	for (i = 0; i < numchars; i++)
		str_topad[i] = padchar;
		
}//		


