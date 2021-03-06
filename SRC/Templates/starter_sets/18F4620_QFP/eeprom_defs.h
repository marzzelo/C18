//+--------------------------------------------------------------------------+
//|       $Workfile:: eeprom_defs.h              $ $Revision:: 2             $
//+--------------------------------------------------------------------------+
//|         $Author:: Mav                                                    $
//|        $Modtime:: 16/06/11 8:36p                                         $
//|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/eeprom_defs. $
//+--------------------------------------------------------------------------+ 

#ifndef EEPROM_DEFS_H
#define EEPROM_DEFS_H

/**************************************************
 *                                                *
 *                  f l a s h                     *
 *                                                *
 **************************************************/
	#define FF_DATA			  0xFFC0 
									 
/**************************************************
 *                                                *
 *         E E P R O M    P A G E   0             *
 *                                                *
 **************************************************/	
#define EE_VAR0				0,0 		
// ... NEXT FREE:           0,1 

/**************************************************
 *                                                *
 *         E E P R O M    P A G E   1             *
 *                                                *
 **************************************************/
#define EE_VAR1				1,0 		
// ... NEXT FREE:           1,1 

/**************************************************
 *                                                *
 *         E E P R O M    P A G E   2             *
 *                                                *
 **************************************************/
#define EE_VAR2				2,0 		
// ... NEXT FREE:           2,1 
			
/**************************************************
 *                                                *
 *         E E P R O M    P A G E   3             *
 *                                                *
 **************************************************/
#define EE_VAR3				3,0 		
// ... NEXT FREE:           3,1 



#endif
