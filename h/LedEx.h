//+--------------------------------------------------------------------------+
//|       $Workfile:: LedEx.h                    $ $Revision:: 1             $
//+--------------------------------------------------------------------------+
//|         $Author:: Marcelo                                                $
//|        $Modtime:: 16/09/08 7:28                                          $
//|        $Archive:: /GSM6410 - 4620/obj/Ledex/LedEx.h                      $
//+--------------------------------------------------------------------------+
#include "typedefs.h"

void LedUpdate(BYTE LEDBUFF); ///< Controla el multiplexado de 8 leds con 4 pines en ISR. (Llamar cada 1ms aprox)
