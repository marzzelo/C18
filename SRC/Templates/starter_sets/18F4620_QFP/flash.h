//+--------------------------------------------------------------------------+
//|       $Workfile:: flash.h                    $ $Revision:: 1             $
//+--------------------------------------------------------------------------+
//|         $Author:: Mav                                                    $
//|        $Modtime:: 7/05/11 1:37p                                          $
//|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/flash.h      $
//+--------------------------------------------------------------------------+ 

#ifndef FLASH_H
#define FLASH_H

/*************************************************************************//** 
* @Descripcion	escribe en FLASH un bloque de 64 bytes de datos desde RAM					
* @param[in]	address  Dirección base en la memoria de programa (FLASH)
*						 donde se escribiran los datos.
* @param[in]	*buffer	 Puntero a un buffer en RAM conteniendo los datos
* @test
* @code			FFwrite(0x7C00, myData);                             @endcode
*
* $Author: Mav $ $Revision: 1 $ $Date: 16/06/11 4:59p $ 			
*****************************************************************************/
char FFwrite(unsigned long FFaddress, const unsigned char *buffer);


/*************************************************************************//** 
* @Descripcion	Lee desde FLASH un bloque de 64 bytes de datos hacia RAM					
* @param[in]	address  Dirección base en la memoria de programa (FLASH)
*						 desde donde se leerán los datos.
* @param[in]	*buffer	 Puntero a un buffer destino en RAM 
* @test
* @code			FFread(myData, 0x7C00);                              @endcode
*
* $Author: Mav $ $Revision: 1 $ $Date: 16/06/11 4:59p $ 			
*****************************************************************************/
void FFread(unsigned char *buffer, unsigned long FFaddress);


#endif
