//+------------------------------------------------------------------+
//|       $Workfile:: main.h                     $ $Revision:: 4     $
//+------------------------------------------------------------------+
//|         $Author:: Mav                                            $
//|        $Modtime:: 19/06/11 10:15p                                $
//|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/main $
//+------------------------------------------------------------------+


#ifndef _GSM_H
#define _GSM_H

#include "constantes.h"
#include "fsm.h"
#include "delayer.h"
#include "typedefs.h"
#include "fgreader.h"


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


// D A T A  (GLOBALS)
extern Fsm myFsm;
extern Delayer myDelay;
extern Reader reader1;

#endif	

