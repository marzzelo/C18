//+--------------------------------------------------------------------------+
//|  $Workfile:: Iterators.h                             $ $Revision:: 2     $
//+--------------------------------------------------------------------------+
//|  $Author:: Mav                                                           $
//|  $Modtime:: 29/11/11 12:30p                                              $
//|  $Archive:: /@C18/SRC/MTS/Iterators.h                                    $
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
 *						(se pasa el índice de bit: int [0..7])
 * @param[in]	iterFunct	delegado del tipo BitIterator 
 * @param[in]	*parms	puntero que será pasado a la función como 2º parm.
 * @test		
 * @code        ForEachBit(mask, SetPeriod, (void *)&theseParms);
 *                                                      			  @endcode
 ****************************************************************************/
void ForEachBit(uint8_t 	mask, 
				BitIterator iterFunct, 
				void 		*parms);
