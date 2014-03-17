//+--------------------------------------------------------------------------+
//|  $Workfile:: Iterators.h                             $ $Revision:: 1     $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 18/10/10 9:02p                                               $
//|  $Archive:: /@CODE/obj/iterators/Iterators.h                             $
//+--------------------------------------------------------------------------+

#ifndef XUSART_H
#define XUSART_H 

#include "typedefs.h"

/*-- Delegados -------------------------------------------------------------*/
typedef void (*BitIterator)(uint8_t i, void *parms);

/*-- Prototipos ------------------------------------------------------------*/


/*************************************************************************//** 
 * @Descripcion	Ejecuta la funci�n 'iterFunct()' una vez por cada bit  
 * 				seteado en la mascara 'mask', con parms como par�metro.
 * @param[in]	mask	byte de m�scara cuyos bits seteados determinar�n el
 *						primer par�metro a pasar a la funci�n iterFunct()
 * @param[in]	iterFunct	delegado del tipo BitIterator 
 * @param[in]	*parms	puntero que ser� pasado a la funci�n como 2� parm.
 * @test		
 * @code        ForEachBit(mask, SetPeriod, (void *)&theseParms);
 *                                                      			  @endcode
 ****************************************************************************/
void ForEachBit(uint8_t 	mask, 
				BitIterator iterFunct, 
				void 		*parms);
