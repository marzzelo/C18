//;+------------------------------------------------------------------+
//;|       $Workfile:: strInsert.c                $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 10/12/09 10:48p                                $
//;|        $Archive:: /@CODE/obj/xstrings/strInsert.c                $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>


/*****************************************************************//** 
$Revision: 2 $  <hr>
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
