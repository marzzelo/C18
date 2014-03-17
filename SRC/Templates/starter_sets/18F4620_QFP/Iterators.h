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
 * @Descripcion	Ejecuta la función 'iterFunct()' una vez por cada bit  
 * 				seteado en la mascara 'mask', con parms como parámetro.
 * @param[in]	mask	byte de máscara cuyos bits seteados determinarán el
 *						primer parámetro a pasar a la función iterFunct()
 * @param[in]	iterFunct	delegado del tipo BitIterator 
 * @param[in]	*parms	puntero que será pasado a la función como 2º parm.
 * @test		
 * @code        ForEachBit(mask, SetPeriod, (void *)&theseParms);
 *                                                      			  @endcode
 ****************************************************************************/
void ForEachBit(uint8_t 	mask, 
				BitIterator iterFunct, 
				void 		*parms);
