//+------------------------------------------------------------------+
//|       $Workfile:: main.h                     $ $Revision:: 5     $
//+------------------------------------------------------------------+
//|         $Author:: Mav                                            $
//|        $Modtime:: 20/11/11 12:28a                                $
//|        $Archive:: /@C18/SRC/Templates/starter_sets/18F4620_OOP/m $
//+------------------------------------------------------------------+


#ifndef _GSM_H
#define _GSM_H

#include "constantes.h"
#include "typedefs.h"


// M A C R O S    G L O B A L E S

// E S T R U C T U R A S    G L O B A L E S  
CLASS(MyType)
	char *cmd;
	char *parms[];
METHODS
	// constructor:
	MyType *MyTypeCtor_(MyType *me, int* somePresetValue);
	
	// metodos
	int* MyType_start(MyType *me, int someParameter); 	
	// definir otros métodos
END_CLASS


// E N U M E R A C I O N E S    G L O B A L E S           
typedef enum RcEnumTag {
	RC_RUNNING 		= 0,
	RC_FINISHED 	= 1,
	RC_ERROR 		= 2,
	RC_NEEDFULLTIME = 3,
	RC_TIMEOUT 		= 99
} RcEnum;




#endif	

