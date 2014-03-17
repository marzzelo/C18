/* Definiciones para carga directa de registros */

#ifndef _P18FXXX_DEFS_H
#define _P18FXXX_DEFS_H

#if   defined(__18F4550)
  #include <P18F4550_DEFS.h>
  
#elif defined(__18F452)
  #include <P18F452_DEFS.h>
   
#elif defined(__18F4520)
  #include <P18F4520_DEFS.h>
  
#elif defined(__18F4620)
  #include <P18F4620_DEFS.h>
  
#elif defined(__18F4685)
  #include <P18F4685_DEFS.h>
    
#elif defined(__18F8722)
  #include "p18f8722_defs.h"
        
    
#else
  #error  <<< PROCESADOR SIN ARCHIVO DE DEFINICIONES >>>
#endif

#endif /* _P18FXXX_DEFS_H */


