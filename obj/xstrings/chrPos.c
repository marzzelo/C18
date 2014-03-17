//;+------------------------------------------------------------------+
//;|       $Workfile:: chrPos.c                   $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 11/12/09 5:58p                                 $
//;|        $Archive:: /@CODE/obj/xstrings/chrPos.c                   $
//;+------------------------------------------------------------------+

#include <string.h>
#include <stdio.h>
#include <xstrings.h>

unsigned char chrPos(const char *str, unsigned char c)
 {
 	return (unsigned char)(strchr(str, c) - str);
 }
 //


