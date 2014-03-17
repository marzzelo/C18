//+--------------------------------------------------------------------------+
//|       $Workfile:: eeprom.h                   $ $Revision:: 10            $
//+--------------------------------------------------------------------------+
//|         $Author:: valdez                                                 $
//|        $Modtime:: 13/01/12 10:55a                                        $
//|        $Archive:: /@C18/SRC/LATCH/eeprom.h                               $
//+--------------------------------------------------------------------------+ 

#ifndef EEPROM_H
#define EEPROM_H

#if (defined(__18F4520) || defined(__18F452))
char EEwrite(unsigned char addr, unsigned char value); ///< Escribe un caracter en la EEprom
char EEread(unsigned char addr); ///< Lee un caracter desde la EEprom
char* EEreadstring(ram char* destino, const unsigned char EEORIGEN); ///< Lee un string desde la EEprom
char* EEwritestring(const unsigned char EE_CALLER_ID, ram char* origen); ///< Escribe un string en la EEprom
char strcmpEE2ram(const char * strram, const unsigned char strEE ); ///< Compara un string en RAM con otro en la EEprom
char* EEwriteN(unsigned char EEstartAddress, const char* ramBuff, unsigned char n); ///< Copia a EEprom el contenido de un buffer en RAM
char* EEreadN(char* ramBuff, unsigned char EEstartAddress, unsigned char n); /// lee varios caracteres desde EEPROM.
int EEwriteInt(unsigned char EEstartAddress, int Int);
int EEreadInt(unsigned char addr);



#elif (defined(__18F4620)  || defined(__18F4685))
/***************************************
 *                                     * 
 * CHAR                                *
 *                                     *
 ***************************************/
char EEwrite(unsigned char page, unsigned char addr, unsigned char value); ///< Escribe un caracter en la EEprom
char EEread(unsigned char page, unsigned char addr); ///< Lee un caracter desde la EEprom
/***************************************
 *                                     * 
 * STRING (0x00 ended)                 *
 *                                     *
 ***************************************/
char* EEreadstring(ram char* destino, const unsigned char page, const unsigned char EEORIGEN); ///< Lee un string desde la EEprom
char* EEwritestring(const unsigned char page, const unsigned char EE_BASE, ram char* origen); ///< Escribe un string en la EEprom
/***************************************
 *                                     * 
 * RAM BUFFER (n bytes)                *
 *                                     *
 ***************************************/
char* EEwriteN(unsigned char page, unsigned char EEstartAddress, const char* ramBuff, unsigned char n); ///< Copia a EEprom el contenido de un buffer en RAM
char* EEreadN(char* ramBuff, unsigned char page, unsigned char EEstartAddress, unsigned char n); /// lee varios caracteres desde EEPROM.
/***************************************
 *                                     * 
 * uint16_t, int16_t                   *
 *                                     *
 ***************************************/
int EEwriteInt(unsigned char page, unsigned char EEstartAddress, int Int);
unsigned int EEwriteUInt(unsigned char page, unsigned char EEstartAddress, unsigned int Int);
int EEreadInt(unsigned char page, unsigned char addr);
unsigned int EEreadUInt(unsigned char page, unsigned char addr);
/***************************************
 *                                     * 
 * uint32_t, int32_t                   *
 *                                     *
 ***************************************/
long EEwriteI32(unsigned char page, unsigned char EEstartAddress, long Int);
unsigned long EEwriteU32(unsigned char page, unsigned char EEstartAddress, unsigned long Int);
long EEreadI32(unsigned char page, unsigned char addr);
unsigned long EEreadU32(unsigned char page, unsigned char addr);
/***************************************
 *                                     * 
 * REFRESCAR EEPROM                    *
 *                                     *
 ***************************************/
void EErefresh(void);
/***************************************
 *                                     * 
 * INCREMENTAR UN ENTERO 16 EN EEPROM  *
 *                                     *
 ***************************************/
int EEincInt(unsigned char page, unsigned char EEstartAddress, int value);
unsigned int EEincUInt(unsigned char page, unsigned char EEstartAddress, unsigned int value);
/***************************************
 *                                     * 
 * COMPARACION DE STRING CONTRA RAM    *
 *                                     *
 ***************************************/
char strcmpEE2ram(const char * strram, const unsigned char page, const unsigned char strEE); ///< Compara un string en RAM con otro en la EEprom

#endif
#endif

