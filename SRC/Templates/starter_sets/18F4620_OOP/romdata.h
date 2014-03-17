//;+------------------------------------------------------------------+
//;|       $Workfile:: romdata.h                  $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 20/06/11 2:05p                                 $
//;|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/romd $
//;+------------------------------------------------------------------+


#pragma romdata factory_defaults = 0xF00000
const rom char fd1sttime = 0xAA; // Obligar a reset PF para inicializar EEprom

#pragma romdata firmwareVersion = 0xF0002A
const rom char firmwareversion = 3;

#pragma romdata statistics = 0xF00030
const rom char stats[20] = {0,0,0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,0,0};			     // Presetear Estadísticas a 0

#pragma romdata
