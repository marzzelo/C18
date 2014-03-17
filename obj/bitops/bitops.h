//;+------------------------------------------------------------------+
//;|       $Workfile:: bitops.h                   $ $Revision:: 4     $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 15/12/11 1:42p                                 $
//;|        $Archive:: /@C18/obj/bitops/bitops.h                      $
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

/** Cuenta los bits a TRUE en un byte */
unsigned char countbits(unsigned char b);
uint8_t countbitsU32(uint32_t b);

#endif
