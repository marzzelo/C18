//;+------------------------------------------------------------------+
//;|       $Workfile:: xstrings.h                 $ $Revision:: 23    $
//;+------------------------------------------------------------------+
//;|         $Author:: valdez                                         $
//;|        $Modtime:: 18/12/13 9:42                                  $
//;|        $Archive:: /@C18/SRC/ADAQUS/xstrings.h                    $
//;+------------------------------------------------------------------+
#ifndef _xstrings_h
#define _xstrings_h

/**********************************************************************
 *            I N D I C E    D E    F U N C I O N E S                 *
 **********************************************************************
void 			strinsert	(char* str_dest,const char* str_source,const char* str_rep);
void 			strextract	(char* str_dest, char* str_source);
void 			bintable	(char* str_symbol,const char* str_bin,char zero,char one,char dir);				
void 			padl	(char* str_topad,char padchar,unsigned char numchars);
far rom char 	*byte2dowstr	(unsigned char dowbyte);
unsigned char 	dowstr2byte	(const char *dowstr);
unsigned char 	dowchr2byte	(char dowchr);
char 			byte2dowchr	(unsigned char dowbyte);
unsigned char 	chrPos	(const char *str, unsigned char c);
int 			strcatf	(char *dest, const char *src, unsigned int sizeOfDest);
int 			strcatfpgm2ram	(char *dest, const far rom char *src, sizerom_t sizeOfDest);
unsigned char 	strLocate	(const char *str1,far rom const char *table[],unsigned char compLen,unsigned char table_size);
void 			split	(char *line,char *parms[],unsigned char nWords,const far rom char *delims);
unsigned char 	list2byte	(const char* list,unsigned char base,unsigned char maxDigit);
char 			*byte2list	(unsigned char mask,unsigned char base);
void 			secs2hhmmss	(char* hhmmss, unsigned int secs);						
void 			ftos	(float fd, char s[], unsigned int multiplier);	
*/

/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
void 			strinsert(	char* str_dest, 
						  	const char* str_source, 
							const char* str_rep);

/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
void 			strextract(	char* str_dest, char* str_source);

/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
void 			bintable(	char* str_symbol, 
							const char* str_bin, 
							char zero, 
							char one, 
							char dir);				

/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
void 			padl(		char* str_topad, 
							char padchar, 
							unsigned char numchars);
							

/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// ([0..6]) --> ["DOM".."SAB"]							
far rom char *byte2dowstr(unsigned char dowbyte);


/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// (['D'..'S']) --> [0..6]  
// ('I') --> 3
unsigned char dowstr2byte(const char *dowstr);
unsigned char dowchr2byte(char dowchr);


/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// ([0..6]) --> ['D'..'S']
// (3) --> 'I'
char byte2dowchr(unsigned char dowbyte);


/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// ("HOLA MUNDO",'A') --> 3
unsigned char chrPos(const char *str, unsigned char c);
							
							
/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// (HOLA\0·······, MUNDO\0, 12) -> HOLA MUNDO\0·· -> +2
// (HOLA\0···, MUNDO\0,	 	 8) -> HOLA\0···      -> -3					
int strcatf(char *dest, const char *src, unsigned int sizeOfDest);
int strcatfpgm2ram(char *dest, const far rom char *src, sizerom_t sizeOfDest);
							
							
/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
// (BETA\0, {"ALFA", "BETA", "GAMMA"}, 0, 3)  ->  1
// (ALFA\0, {"ALFA", "BETA", "GAMMA"}, 0, 3)  ->  0
// (GAMMA\0, {"ALFA", "BETA", "GAMMA"}, 0, 3) ->  2
// (MOUSE\0, {"ALFA", "BETA", "GAMMA"}, 0, 3) ->  3 (NOT FOUND)
// (BETARGET\0, {"ALFA", "BETA", "GAMMA"}, 0, 3)  ->  3 (NOT FOUND)
// (BETARGET\0, {"ALFA", "BETA", "GAMMA"}, 4, 3)  ->  1
// (BETARGET\0, {"ALFA", "BETA", "GAMMA"}, 3, 3)  ->  1
// (BETARGET\0, {"ALFA", "BETA", "GAMMA"}, 5, 3)  ->  3 (NOT FOUND)							
unsigned char strLocate(	const char *str1, 
							far rom const char *table[],
							unsigned char compLen, 
							unsigned char table_size);
							
							
/*************************************************************************//** 
 * Descripcion_breve. Descripcion_detallada
 * @param[in]    
 * @param[out]   
 * @returns      
 * @test         
 ****************************************************************************/
//DATA:
//	char 	buff[80];
//	char 	*line1[NPARMS];;
//	frchar 	delims[] = " \"\n\r,;=";  				
//CODE:
//	Split(buff, line1, delims);								
void split(					char *line, 
							char *parms[], 
							unsigned char nWords,
							const far rom char *delims);
							
							
/*************************************************************************//** 
 * @Descripcion	Convierte una lista de números en ASCII (ej: 12367) en un 
 *				byte con sus bits correspondientes seteados a 1
 * @param[in]	list	string conteniendo los números en ASCII (0-9)
 * @param[in]	base	número que corresponde al bit 0 (gral~ 0 ó 1)
 * @param[in]	maxDigit	máximo valor permitido en la cadena (entre 0 y 9)	
 * @test
 * @code        byte myByte = list2byte(myList, 1, 7);				@endcode
 ****************************************************************************/										
unsigned char list2byte(	const char* list, 
							unsigned char base, 
							unsigned char maxDigit);
							
char *byte2list(			unsigned char mask, 
							unsigned char base);

/*************************************************************************//** 
 * Segundos a hh:mm:ss.
 * Convierte un uint_16 representando segundos al formato hh:mm:ss.
 * @param[in]    secs [hasta 65535]
 * @param[out]   hhmmss se requiere un buffer inicializado a "00:00:00"
 * @returns      void
 * @test         char hms[] = "00:00:00";
 *				 secs2hhmmss(hms, 3661);
 *				 3661 --> "01:01:01"
 ****************************************************************************/
void secs2hhmmss(char* hhmmss, unsigned int secs);						


/*************************************************************************//** 
Convierte un float a string para poder imprimirlo con printf.
@param[in]	fd    	Float a convertir toString
@param[out] s		puntero al string de salida
@param[in]  multiplier  indicador de decimales deseados (100: 2 decimales,
			1000: 3 decimales o 10000: 4 decimales)
*****************************************************************************/
void ftos(float fd, char s[], unsigned int multiplier);													

#endif  
//

