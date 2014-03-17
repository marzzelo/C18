//;+------------------------------------------------------------------+
//;|       $Workfile:: bitops.h                   $ $Revision:: 3     $
//;+------------------------------------------------------------------+
//;|         $Author:: Marcelo                                        $
//;|        $Modtime:: 11/03/10 8:54p                                 $
//;|        $Archive:: /@CODE/obj/bitops/bitops.h                     $
//;+------------------------------------------------------------------+
 

#ifndef _bitops_h
#define _bitops_h

#include "typedefs.h"

/* WORD FUNCTIONS */
WORD bitsetw(WORD* intflag, char bt);
WORD bitresetw(WORD* intflag, char bt);
WORD bitgetw(const WORD* intflag, char bt);

/* DWORD FUNCTIONS */
DWORD bitsetdw(DWORD* dwflag, char bt);
DWORD bitresetdw(DWORD* dwflag, char bt);
DWORD bitgetdw(const DWORD* intflag, char bt);

unsigned char maxBit(unsigned char mask);
unsigned char minBit(unsigned char mask);

#endif
