//;+------------------------------------------------------------------+
//;|       $Workfile:: flags.h                    $ $Revision:: 2     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 16/06/11 8:38p                                 $
//;|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/flag $
//;+------------------------------------------------------------------+

	
/**************************************************
 *  FLAGS 1                                       *
 **************************************************/
extern BYTE FLAGS1;
	#define B1READY				FLAGS1.b0	
	#define B2READY				FLAGS1.b1	

		#define B1READY_bit             0
        #define B2READY_bit             1

/**************************************************
 *  FLAGS 2                                      *
 **************************************************/
extern BYTE FLAGS2;
	#define PRI_READY			FLAGS2.b0	
	#define NO_MORE_USERS		FLAGS2.b1	


/**************************************************
 *  FLAGS 3                                       *
 **************************************************/	
extern BYTE FLAGS3;
	#define USE_MAIL			FLAGS3.b0	
	#define SONO				FLAGS3.b1	

