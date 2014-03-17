#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/* Standard Macros */

#define strncpypgm2ram_(A, B, C)        strncpypgm2ram((A), (frchar *)(B), (C))
#define strncatpgm2ram_(A, B, C)        strncatpgm2ram((A), (frchar *)(B), (C))
#define strcpypgm2ram_(A, B)            strcpypgm2ram((A), (frchar *)(B))
#define strstrrampgm_(A, B)             strstrrampgm((A), (frchar *)(B))
#define strcatpgm2ram_(A, B)            strcatpgm2ram((A), (frchar *)(B))


#define printf_(A)                                      printf((frchar*)(A))
#define printf__(A,B)                           printf((frchar*)(A),(B))
#define printf___(A,B,C)                        printf((frchar*)(A),(B),(C))

#define sprintf_(BUFF, A)                       sprintf((BUFF), (frchar*)(A))
#define sprintf__(BUFF, A,B)            sprintf((BUFF), (frchar*)(A),(B))
#define sprintf___(BUFF, A,B,C)         sprintf((BUFF), (frchar*)(A),(B),(C))



/* helper macro to calculate static dimension of a 1-dim array */
#define DIM(array_) (sizeof(array_)/sizeof(*(array_)))


//+----------------------------------------------------------------------------+
//|                              T Y P E D E F S                               |
//+----------------------------------------------------------------------------+
typedef unsigned char   byte;           ///< 8-bit - Sirve como base para otros tipos como BYTE
typedef unsigned int    word;           // 16-bit
typedef unsigned long   dword;          // 32-bit


/**************************************************************************//** 
@brief El tipo BYTE permite direccionar bits individuales de un registro de la ram 
                                mediante los miembros b0, b1..., b7, así como al registro completo 
                                mediante el miembro _byte.
 
@warning                No confundir con el tipo \b byte que direcciona un registro completo
                                únicamente.
@test 
@code           BYTE B;                                             @endcode
@code           B.b0 = 1;                                           @endcode
@code           B.b1 = 0;                                                       @endcode
@code           B._byte = 0x00;                                                     @endcode
**************************************************************************** **/
typedef union _BYTE
        {
    unsigned char _byte;
    struct
        {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
        };
        } BYTE;
        
/**************************************************************************//** 
@brief   El tipo WORD permite direccionar bits individuales de una palabra 
                                de 16 bits de la ram mediante los miembros .Byte0.b0, .Byte0.b1...
                                .Byte1.b0, .Byte1.b1... así como a bytes completos dentro de la
                                palabra, mediante los miembros byte0 y byte1.
 
@test 
@code           WORD W;                                             @endcode
@code   (1)     W.byte0 = 0x00;                                     @endcode
@code           W.byte1 = 0xFF;                                                 @endcode

@code   (2)     W.Byte0.b0 = 0;                                                     @endcode
@code           W.Byte1.b0 = 0;                                                     @endcode

@code   (3)     W.LowB.b0  = 1;                                                     @endcode
@code           W.HighB.b0 = 1;                                                     @endcode

@code   (4)     W.byte[0] = 0xAA;                                                   @endcode
@code           W.byte[1] = 0xEE;                                                   @endcode

@code   (5)     LSB(W) = 0x00;                                                              @endcode
@code           HSB(W) = 0x11;                                                      @endcode

@code   (6)     W.Byte0._byte = 0x22; // conviene (1)                       @endcode
@code           W.Byte1._byte = 0x44;                                               @endcode

**************************************************************************** **/
typedef union _WORD
{
    word _word;
    struct
    {
        byte byte0;
        byte byte1;
    };
    struct
    {
        BYTE Byte0;
        BYTE Byte1;
    };
    struct
    {
        BYTE LowB;
        BYTE HighB;
    };
    struct
    {
        byte v[2];
    };
} WORD;



/*********************************/
typedef union _WORD3
{
    unsigned short long _word3;
    struct
    {
        byte byte0;
        byte byte1;
                byte byte2;
    };
    struct
    {
        BYTE Byte0;
        BYTE Byte1;
                BYTE Byte2;
    };
    struct
    {
        BYTE LowB;
        BYTE MedB;
        BYTE HighB;
    };
    struct
    {
        byte v[3];
    };
} WORD3;

#define LSB(a)      ((a).v[0])
#define MSB(a)      ((a).v[1])
#define USB(a)      ((a).v[2])



/**************************************************************************//** 
@brief   El tipo DWORD permite direccionar bits individuales de una palabra 
                                de 32 bits de la ram mediante los miembros .Byte0.b0 ... .Byte3.b7
                                así como a bytes completos dentro de la
                                palabra, mediante los miembros byte0 y byte1.
 
@test 

@code           WORD W;                                             @endcode

@code   (1)     W.byte0 = 0x00;                                     @endcode
@code           W.byte1 = 0xFF;                                                 @endcode

@code   (2)     W.Byte0.b0 = 0;                                                     @endcode
@code           W.Byte1.b0 = 0;                                                     @endcode

@code   (3)     W.LowB.b0  = 1;                                                     @endcode
@code           W.HighB.b0 = 1;                                                     @endcode

@code   (4)     W.byte[0] = 0xAA;                                                   @endcode
@code           W.byte[1] = 0xEE;                                                   @endcode

@code   (5)     LSB(W) = 0x00;                                                              @endcode
@code           HSB(W) = 0x11;                                                      @endcode

@code   (6)     W.Byte0._byte = 0x22; // conviene (1)                       @endcode
@code           W.Byte1._byte = 0x44;                                               @endcode

**************************************************************************** **/
typedef union _DWORD
{
    dword _dword;
    struct
    {
        byte byte0;
        byte byte1;
        byte byte2;
        byte byte3;
    };
    struct
    {
        word word0;
        word word1;
    };
    struct
    {
        BYTE Byte0;
        BYTE Byte1;
        BYTE Byte2;
        BYTE Byte3;
    };
    struct
    {
        WORD Word0;
        WORD Word1;
    };
    struct
    {
        byte v[4];
    };
} DWORD;


#define LOWER_LSB(a)    ((a).v[0])
#define LOWER_MSB(a)    ((a).v[1])
#define UPPER_LSB(a)    ((a).v[2])
#define UPPER_MSB(a)    ((a).v[3])


typedef void(*pFunc)(void);

typedef far rom void frvoid;                    ///< Usado para casting en funciones como strcmppgm2ram()
typedef char rom const crchar;
typedef char rom far const frchar;              ///< Usado para casting en funciones como memcmppgm2ram()

//+---------+
//| POINTER |
//+---------+
typedef union _POINTER
{
    struct
    {
        byte bLow;
        byte bHigh;
        //byte bUpper;
    };
    word _word;                         // bLow & bHigh
    
    //pFunc _pFunc;                       // Usage: ptr.pFunc(); Init: ptr.pFunc = &<Function>;

    byte* bRam;                         // Ram byte pointer: 2 bytes pointer pointing
                                        // to 1 byte of data
    word* wRam;                         // Ram word poitner: 2 bytes poitner pointing
                                        // to 2 bytes of data

    rom byte* bRom;                     // Size depends on compiler setting
    rom word* wRom;
    //rom near byte* nbRom;               // Near = 2 bytes pointer
    //rom near word* nwRom;
    //rom far byte* fbRom;                // Far = 3 bytes pointer
    //rom far word* fwRom;
} POINTER;

//+--------------+
//| FALSE / TRUE |
//+--------------+
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;

#define HIGH      TRUE
#define LOW       FALSE

#define null 0
#define NULL 0

/*************************************************************************//**
 Puerto digital de I/O
 ****************************************************************************/
typedef volatile near unsigned char port_t;  // ej.: 	port_t *puerto

/***************************************************************************
 Dirección completa eeprom
 ****************************************************************************/
typedef struct AddressTag {
        unsigned char   page;
        unsigned char   offset;
} Address;

/*************************************************************************//**
 Exact-width types. WG14/N843 C99 Standard, Section 7.18.1.1 
 ****************************************************************************/ 
typedef signed   char       int8_t;
typedef signed   int        int16_t;
typedef short long          int24_t;
typedef signed   long       int32_t;

typedef unsigned char       uint8_t;
typedef unsigned int        uint16_t;
typedef unsigned long       uint32_t;
typedef unsigned short long uint24_t;

/**
 * Macros for declaring simple classes (without polymorphism)
 */
#define CLASS(name_)          \
   typedef struct name_ name_; \
   struct name_ {
#define METHODS };
#define END_CLASS



/** Tipo para el Manejador de eventos */
typedef void (*EventHandler)(void);
typedef void (*Handler)(void*);		// (void*) : Container Object (parent)

#define INT_LOCK(key_)       do { \
    (key_) = (INTCON & 0b11000000); \
    INTCON &= 0b00111111; \
} while (0)
#define INT_UNLOCK(key_)     (INTCON |= (key_))


#endif //TYPEDEFS_H
