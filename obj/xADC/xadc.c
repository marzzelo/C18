/**********************************************************************
*    Processor:      P18F4550                                         *
*    Description:    ANALOG / DIGITAL module control header           *
**********************************************************************/

// Written By: Marcelo Valdéz, DOBA Embedded Systems
// MPLAB-C18 compliler ver. 3.00 (demo)
//
// Revision History
// 25-06-06		Version inicial

#include <p18cxxx.h>	// ADRESH, ADRESL
#include "xadc.h"		// union ADResult, ReadADC prototype

/********************************************************************
*    Function Name:  ReadAD                                         *
*    Return Value:   int, A/D result                                *
*    Parameters:     void                                           *
*    Description:    This routine reads the ADRESL and ADRESH       *
*                    and returns these as a long.                   *
********************************************************************/
int ReadADC( ) 
{
	ADResult ADR;
	
	
 	ADR.MSB = ADRESH;
	ADR.LSB = ADRESL;
	return ADR.INT;
}//
