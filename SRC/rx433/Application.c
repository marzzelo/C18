//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 82    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 23/12/13 13:14                                 $
//|        $Archive:: /@C18/SRC/rx433/Application.c                  $
//+------------------------------------------------------------------+

/*************************************************************************//** 
 * @file    Application.c
 * @brief	Decodificador RX 433MHz 24bits 4Channels
 ****************************************************************************/

/* MACROS */
#define _NASSERT  /* quitar el guion para deshabilitar assertions */

#include "ifcondic.h"
#include "qassert.h"		
DEFINE_THIS_FILE; /* definido en qassert.h, para usar con ASSERT(test) etc. */

/* STANDARD LIBRARIES */
#include <p18cxxx.h>
#include <string.h>			
#include <stdlib.h>					
#include <stdio.h>	

#include "xusart.h"

/* USER DEFINITIONS */
#include "fuses_8722.h"
#include "init_pic.h"					
#include "p18fxxx_defs.h" 
#include "typedefs.h"   
#include "xstrings.h"
#include "eeprom.h"

/* CLASES */
#include "UartReader.h"
#include "UartWriter.h"
#include "Relay.h"
#include "CButton.h"
#include "daq.h"
#include "rxReceiver.h"

#include "application.h" // definición del objeto Aplicacion
#include "isr.h"
#include "io_cfg.h"

#pragma romdata
static far rom const char *cmds[]= {
	"list",		"dummy1",	"reset",	"setup",
	"start",	"stop",		"pause",	"resume",
	"echo",		"copy",		"enable",	"save",
	"load",		"preset",	"address",	"help",
	"scale",	"cycles",	"acquire",	"amp"
};

typedef enum Cmd_ {
	CMD_LIST=0,		CMD_SET,		CMD_RESET,		CMD_SETUP,
	CMD_START,		CMD_STOP,		CMD_PAUSE,		CMD_RESUME,
	CMD_ECHO,		CMD_COPY,		CMD_ENABLE,		CMD_SAVE,
	CMD_LOAD,		CMD_PRESET,		CMD_ADDRESS,	CMD_HELP,	
	CMD_SCALE,		CMD_CYCLES,		CMD_ACQUIRE,	CMD_AMP,

	CMDS__MAX
} Cmd;

frchar STR_MASTER_SET[] = "\r\n%d --> master.\r\n\r\n";
frchar STR_FORMAT_ERROR[] = "\r\nFormat ERROR.\r\n\r\n";
frchar STR_RELAYS_SET[] = "\r\nRelays Set.";
frchar STR_ALREADY_STOP[] = "[Ya está detenido]";
frchar STR_ALREADY_PAUSED[] = "[Ya está pausado]";
frchar STR_ALREADY_RUNNING[] = "[Está corriendo]";
frchar STR_UNKNOWN_CMD[] = "ERROR: comando desconocido %s";
frchar STR_ALL_DISABLED[] = "\r\nERROR: ningún canal habilitado";
frchar STR_START[] = "Iniciando... [FEEDBACK: %S]\r\n";
frchar STR_CONTINUE[] = "[Continua]";
frchar STR_STOPPED[] = "[Detenido]";
frchar STR_PAUSED[] = "[Pausado...]";
frchar STR_SETTINGS_RESET[] = "\r\nSETTINGS RESET.";
frchar STR_TIME[] = "\r\n[%s]";
frchar STR_N[] = " %4u,";
frchar STR_DONE[] = "[COMPLETADO]";
frchar STR_BUFFER_FULL[] = "WRITE BUFFER FULL";
frchar STR_ECHO[] = "[ECHO %S]";
frchar STR_STOPFORLIST[] = "[detener para listar]";
frchar STR_LIST_HEADER[] = "\r\nch#     Ton    Toff    Offs    Cycl     Cnt    StHi     Ena\r\n";
frchar STR_LIST_ITEMS[] = "%c%c%u%8u%8u%8u%8u%8u%8u%8c\r\n";
frchar STR_LIST_FOOTER[] = ">:index, f:feedback";
frchar STR_DATA_SAVED[] = "\r\nDatos Guardados";
frchar STR_DATA_LOADED[] = "\r\nDatos Cargados";
frchar STR_NO_FEEDBACK[] = "[--NO FEEDBACK--]";
frchar STR_CYCLES_SET[] = "\r\ncycles set to %u for all";


frchar STR_TITLE1[] = "\r\n\n\n\n\nRELAY MULTIPLEXER\r\nLaboratorio de Experimental\r\nFábrica de Aviones Córdoba";
frchar STR_TITLE3[] = "\r\n----------------------------\r\n\r\n";
frchar STR_HELP[] = "\r\n\nCOMANDOS DISPONIBLES:\r\n\taddress <0..31>\r\n\tamp <0..7>\r\n\tacquire [<from> <to>]\r\n\tsetup <tsa><tsw><nsw><from><to>\r\n\thelp";

frchar STR_READY[] = "\r\n\r\nLISTO>";
frchar STR_SCALE_SET[] = "\r\nScale factor=%s set";

frchar STR_ADDRESS_SET[] = "\r\nAddress %d set\r\n";
frchar STR_ACQUIRING[] = "\r\nAdquiriendo...";
frchar STR_ACQHEADER[] = "\r\n===== RESULTADOS =====\r\nCH\tVAL";
frchar STR_ACQDATA[] = "\r\n%2u\t%s";
frchar STR_SETUP[] = "\r\nSETTINGS:\r\n\tdt sampling: %u\r\n\tdt sweep: %u\r\n\t# samples (per/ch): %u\r\n\tfrom ch: %u\r\n\tto ch: %u\r\n";


#pragma udata BUFFDATA1
char wbuffer[60]; 
char rbuffer[60];

#pragma udata BUFFDATA2
char cmd[30] = {0};
char ans[30] = {0};


#pragma udata BUFFDATA3
DaqBuff adBuff;	// Buffer auxiliar para copia de datos adquiridos en cBuff

char time[10];

char eols[] = "\0\r\n+";
frchar delims[] = " ;";
frchar on[] = "ON";
frchar off[] = "OFF";

char *onoff;
uint16_t cnt = 0;
uint16_t n;
uint32_t tc, sec;

					
// Singleton definition						
#pragma udata APPDATA
Application app; 	

#pragma udata BUFFDATA
CBuff wBuffer;		// Buffer de escritura
CBuff rBuffer;		// Buffer de lectura


uint8_t rIndex;		// Index relay 
uint8_t rFeedback;	// Feedback relay

Relay relay[8];


/* H A N D L E R S */  
static void onStringReceived(ReaderRc rrc);			///< String Recibido por puerto Serie
static void app_onWBufferFull(void);				///< Buffer de escritura lleno

static void onStartTon(uint8_t relay_id);			
static void onStartToff(uint8_t relay_id);
static void onCyclesCompleted(uint8_t relay_id);

// para CButtons
static void onSw1Press(void);						///< S1 presionado
static void onSw1Release(void);						///< S1 soltado
static void onSw1LongPress(void);					///< S1 presionado (Largo)
static void onSw1LongRelease(void);					///< S1 soltado (Largo)

static void onSw2Press(void);						///< S1 presionado
static void onSw2Release(void);						///< S2 soltado
static void onSw2LongPress(void);					///< S2 presionado (Largo)
static void onSw2LongRelease(void);					///< S2 soltado (Largo)

static void onSw3Press(void);						///< S3 presionado

// para DAQ
static void onNSweeps(void*);

// para Application
static void App_ctor(Application *me);  // Constructor
static void App_run(Application *me);

static void prompt(void);

/* RX RECEIVER */
void onRFStart();
void onRFButton();

 
/***************************************
 *                                     *
 *           V E C T O R S             *
 *                                     *
 ***************************************/
#pragma code ISRH_CODE = 0x08		
void high_vector() {_asm goto ISRH _endasm	} //
#pragma code ISRL_CODE = 0x18
void low_vector() {_asm goto ISRL _endasm	} //
#pragma code


/*==========================================================================*/
void main()	
{   
	uint8_t key;

	INT_LOCK(key);		// Disable interruptions
		InitSFR();
		App_ctor(&app);   	// Construye todos los objetos hijos
	INT_UNLOCK(key);	// enable interruptions
	//app_sendMsg(MSG_LOAD);
	App_run(&app);

}//
/*==========================================================================*/


/*************************************************************************//** 
 * App_run. Bucle principal de la aplicacion.
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 * @related     Application
 ****************************************************************************/
static void App_run(Application *me) {
	
    #define NPARMS 8
	char *parms[NPARMS];
	uint8_t i = 0, k;
	uint8_t loc; 
	uint8_t infoleds = 0, stleds;
	
	while (TRUE) 
	{
		ClrWdt();
		theUartWriter_update();
				   
        if (app_getMsg() == BUFF_EMPTY) 
			continue;
			
		
			
		// MESSAGE RECEIVED -----------------------------
		switch (me->_msg)
        {	
        	case MSG_STR_RECEIVED:
        	BUZZ = 0;  // Cualquier mensaje por consola apaga el buzzer
              				
			// Copiar el comando desde cUartBuff en cmd[] 
			CBuff_popString(&rBuffer, cmd);
			
			split(cmd, parms, NPARMS, delims);
			loc = strLocate(parms[0], cmds, 0, CMDS__MAX);	
		
			printf((frchar*)"\r\n[%d]=%s(%s,%s,%s,%s,%s,%s)\r\n", 
					loc, 
					cmd, 
					parms[1], parms[2], 
					parms[3], parms[4],
					parms[5], parms[6]);
			//#endif 
			
			switch (loc)
			{				
				
				case CMD_AMP:
					DAQ_setAmp(&daq, parms[1][0] - '0');
					prompt();
					break;
					
				case CMD_SETUP: {
					uint16_t dtsa = atoi(parms[1]);
					uint16_t dtsw = atoi(parms[2]);
					uint16_t nsa = atoi(parms[3]);
					uint8_t from = atoi(parms[4]);
					uint8_t to = atoi(parms[5]);
					
					DAQ_setup(&daq, dtsa, dtsw, nsa, from, to);
					
					printf(STR_SETUP,
							dtsa, dtsw,
							daq._nSamplesPerChannel,
							daq._fromCh,
							daq._toCh);
					prompt();
					break;
				}	
				
				
				case CMD_CYCLES: {

					break;
				}	
				
				case CMD_HELP:
					printf(STR_HELP);
					prompt();
					break;
					
				case CMD_ADDRESS:
					i = atoi(parms[1]);
					DAQ_outputAddress(&daq, i);
					printf(STR_ADDRESS_SET, i);
					prompt();
					break;
				
				case CMD_COPY: 
					
					break;
				
				case CMD_ENABLE:
					
					break;
					
				case CMD_PRESET:
				
					break;
				
				case CMD_RESET:
					App_ctor(&app);   	
					break;
					
				case CMD_START:
					
					break;
				
				case CMD_STOP:
					
					break;
				
				case CMD_PAUSE:
					
					break;
				
				case CMD_RESUME:
					switch (me->_state) {
						case ST_PAUSED:
						case ST_IDLE:
							app_sendMsg(MSG_RESUME);		
							break;
						case ST_RUNNING:
							printf(STR_ALREADY_RUNNING);
							break;
					}
					break;
					
				case CMD_LIST:
					app_sendMsg(MSG_LIST);
					break;
					
				case CMD_ECHO:
					app_sendMsg(MSG_ECHO_TOGGLE);
					break;	
					
				case CMD_SAVE:
					app_sendMsg(MSG_SAVE);
					break;
					
				case CMD_LOAD:
					app_sendMsg(MSG_LOAD);
					break;
					
					
				case CMD_ACQUIRE:
					DAQ_clearBuff(&daq);
					app_sendMsg(MSG_ACQUIRE);
					break;
									
					
				default:
					switch (me->_state) {
						case ST_IDLE:
							printf(STR_UNKNOWN_CMD, parms[0]);
							prompt();
							break;
					}
					break;
			}
				
			theUartReader_clearBuff();
			theUartReader_start();	// Esperar nuevo comando
			break;
			
			case MSG_START:
				
				break;
	
			
			case MSG_ACQUIRE:
				DAQ_start(&daq);
				printf(STR_ACQUIRING);
				prompt();
				me->_state = ST_IDLE;
				break;
			
			case MSG_RESUME:
								
				break;
				
			case MSG_STOP:
				
				break;
				
			case MSG_PAUSE:
				
				break;
				
			case MSG_RESET:
				
	       		break;
				
			case MSG_TON: 			
				
				break;
				
				
			case MSG_CYCLE_END:
				
				break;
				
	
			case MSG_WBF:
				printf(STR_BUFFER_FULL);
				break;
				
			case MSG_ECHO_TOGGLE:
				me->_ECHO = !me->_ECHO;
				onoff = me->_ECHO? on : off;
				printf(STR_ECHO, onoff);
				break;
	
			case MSG_LIST:
				if (me->_state == ST_RUNNING) {
					strcpypgm2ram(ans, STR_STOPFORLIST);
					CBuff_pushString(&wBuffer,ans);
					break;
				}
				
				//k = (parms[1][0] == NULL)? 0 : parms[1][0] - '0';
				
				printf(STR_LIST_HEADER);
				
				for (k=0;k<8;k++){
					printf(STR_LIST_ITEMS, 
					(k == rFeedback)?'f':' ',
					(k == rIndex)?'>':' ',
					k, 
					relay[k]._Ton, 
					relay[k]._Toff, 
					relay[k]._offset, 
					relay[k]._cycles, 
					relay[k]._cycles - relay[k]._c, 
					relay[k]._STARTS_HI, 
					//relay[k]._PAUSED, 
					relay[k]._ENABLED?'*':'-');
				}
	
				printf(STR_LIST_FOOTER);
				prompt();
	
				break;
				
			case MSG_SAVE:
			{
				uint8_t j;
				
				for (j=0;j<8;j++) {
					EEwriteUInt(EE_TON_ARRAY + 2*j, relay[j]._Ton);
					EEwriteUInt(EE_TOFF_ARRAY + 2*j, relay[j]._Toff);
					EEwriteUInt(EE_OFFSET_ARRAY + 2*j, relay[j]._offset);
					EEwriteUInt(EE_CYCLES_ARRAY + 2*j, relay[j]._cycles);
					//EEwriteUInt(EE_COUNTER_ARRAY + 2*j, relay[j]._c);
	
					EEwrite(EE_RELAY_FLAGS + j, relay[j]._flags._byte);
				}
				EEwrite(EE_INDEX_RELAY, rIndex);
				EEwriteUInt(EE_CNT, cnt);
	
				printf(STR_DATA_SAVED);
				prompt();
				break;
			}	
						
			case MSG_LOAD:
			{
				uint8_t j;
				
				for (j=0;j<8;j++) {
					relay[j]._Ton = EEreadUInt(EE_TON_ARRAY + 2*j);
					relay[j]._Toff = EEreadUInt(EE_TOFF_ARRAY + 2*j);
					relay[j]._offset = EEreadUInt(EE_OFFSET_ARRAY + 2*j);
					relay[j]._cycles = EEreadUInt(EE_CYCLES_ARRAY + 2*j);
					//relay[j]._c = EEreadUInt(EE_COUNTER_ARRAY + 2*j);
					
					relay[j]._flags._byte = EEread(EE_RELAY_FLAGS + j);
				}
				rIndex = EEread(EE_INDEX_RELAY);
				cnt = EEreadUInt(EE_CNT);
				
				printf(STR_DATA_LOADED);
				prompt();
				app_sendMsg(MSG_LIST);
				break;
			}	
			
					   	
	    	// BUTTONS -----------------------------------------------------
	    	
	    	case MSG_SW1_PRESS:
	    		BUZZ = 0;
	            break;
	            
	        case MSG_SW1_RELEASE:
	        	
	            break;
	            
	        case MSG_SW1_LONGPRESS:
	        	
	            break;
	            
	        case MSG_SW1_LONGRELEASE:       	
	        	
	            break;  
	
	        case MSG_SW2_PRESS:
	        	
	            break;
	            
	        case MSG_SW2_RELEASE:
	        	
	            break;
	            
	        case MSG_SW2_LONGPRESS:
	        	
	         	break;  		
	            
	        case MSG_SW2_LONGRELEASE:       	
	        	
	            break; 
	    	
	    	
	    	
	    	case MSG_SWEEP_COMPLETED: 
		    {    	
				float fd;
				ram char sfd[30];
				
				//CBuff_popString(DAQ_getCBuff(&daq), adBuff._buff);
				DAQ_copyDataToExternalBuffer(&daq, adBuff._buff);
				printf(STR_ACQHEADER);
				
				for (i = daq._fromCh; i <= daq._toCh; i++) {
					fd = (float)adBuff._data[i] * 5000.0 / 1024.0;
					ftos(fd, sfd, 100); // nueva función en xStrings.h
	    			printf(STR_ACQDATA, i, sfd);
	   			} 		
				prompt();
	    		break;
	    	}
	    }
    	
	} // while TRUE
}//



/*************************************************************************//** 
 * Constructor
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 * @related     Application
 ****************************************************************************/
static void App_ctor(Application *me) {
	uint8_t i;
	
	
   /***************************************
    *       	 B U F F E R S            *
    ***************************************/
	// Construir los CBuffer para la Uart
	CBuff_ctor(&wBuffer,
		wbuffer,
		DIM(wbuffer),
		app_onWBufferFull);
		
	CBuff_ctor(&rBuffer,
		rbuffer,
		DIM(rbuffer),
		null);
		
	// Construir CBuffer para la cola de mensajes de la app
	CBuff_ctor(&me->_appBuffer,
		me->_appbuffer,
		DIM(me->_appbuffer),
		null);
		
	// Construir el controlador de escritura de la UART
	theUartWriter_ctor(
		&wBuffer, 
		null);
		
	// Iniciar la UART
	theUartWriter_start();
	
	// Construir el controlador de lectura
	#define	TIMEOUT 200L  // (x 10ms)
	theUartReader_ctor(
		&rBuffer, 
		eols, 
		DIM(eols), 
		TIMEOUT, 
		onStringReceived);
		
	theUartReader_start();	
	
   /***************************************
    *     		B U T T O N S             *
    ***************************************/
	CButton_ctor(&me->_sw1,
        &PORTB, 0,
        onSw1Press,
        onSw1Release,
        onSw1LongPress,
        onSw1LongRelease);
							
    CButton_ctor(&me->_sw2,
        &PORTA, 5,
        onSw2Press,
        onSw2Release,
        onSw2LongPress,
        onSw2LongRelease);
        
    CButton_ctor(&me->_sw3,
        &PORTB, 3,
        onSw3Press,
        NULL,
        NULL,
        NULL);
	
	
   /***************************************
    *     		R E L A Y S               *
    ***************************************/	
	for (i=0; i<8; i++) {
		Relay_ctor(&relay[i],
			i, 
			0,
			0,
			0,
			0,
			onStartTon,
			onStartToff,
			onCyclesCompleted,
			TRUE);
		relay[i]._c = 0;
	}
	
   /***************************************
    *     		  D A Q                   *
    ***************************************/	
	#define DTSAMPLE	30
	#define DTSWEEP		1000
	#define NSWEEPS		5
	#define TRISAMASK	0b00001000	// RA3
	#define BASE_PIN	5			// AMP FACTOR EN PINS [5,6,7]
	#define INI_FROM	0
	#define INI_TO		31

 	DAQ_ctor(	&daq, 
  				TRISAMASK,
				VCFG1_VSS, VCFG0_VDD, A4_D12, AD_CH3,
 				&PORTD,
 				&PORTD, BASE_PIN,
 				onNSweeps);
 				
 	DAQ_setup(  &daq,
 				DTSAMPLE, DTSWEEP,
 				NSWEEPS,
 				INI_FROM, INI_TO );
 				
 				
   /* RX RECEIVER */
   theRx_ctor(&PORTA, 0x80, onRFStart, onRFButton);
   theRx_start();
 				
   /***************************************
    *     		  A P P                   *
    ***************************************/	
	rIndex = 0;		// relay usado para conteo de ciclos
	rFeedback = 0;	// relay usado para feedback
		
	// Mensaje inicial
	printf(STR_TITLE1);
	printf(STR_HELP);
	printf(STR_TITLE3);
	
 	printf(STR_SETUP,
			DTSAMPLE, DTSWEEP,
			daq._nSamplesPerChannel,
			daq._fromCh,
			daq._toCh);
			
	prompt();
		
	me->_ECHO = TRUE;	// Inicialmente se muestra el conteo
	// me->_flags1.FEEDBACK = FALSE;
	me->_state = ST_IDLE;  		// estado inicial
}//



/****************************************************************************
 *                                                                          * 
 *                    E V E N T   H A N D L E R S                           *
 *                                                                          *
 ****************************************************************************/
static void onStringReceived(ReaderRc rrc) {
	app_sendMsg(MSG_STR_RECEIVED);
}//


static void app_onWBufferFull() {
	app_sendMsg(MSG_WBF);
}//


/***************************************
 *     		R E L A Y S                *
 ***************************************/	
static void onStartTon(uint8_t relay_id) {
	LATD |= (1 << relay_id);
	if (relay_id == rIndex) {
		app_sendMsg(MSG_TON);
	}	
}//

static void onStartToff(uint8_t relay_id) {
	LATD &= ~(1 << relay_id);
	
	
}//
	
static void onCyclesCompleted(uint8_t relay_id) {
	if (relay_id == rIndex) {
		app_sendMsg(MSG_CYCLE_END);
	}	
}//

/***************************************
 *     		B U T T O N S              *
 ***************************************/
static void onSw1Press() {
    app_sendMsg(MSG_SW1_PRESS);
}
static void onSw1Release() {
    app_sendMsg(MSG_SW1_RELEASE);
}
static void onSw1LongPress() {
	app_sendMsg(MSG_SW1_LONGPRESS);
}
static void onSw1LongRelease() {
	app_sendMsg(MSG_SW1_LONGRELEASE);
}//
static void onSw2Press() {
	app_sendMsg(MSG_SW2_PRESS);
}
static void onSw2Release() {
    app_sendMsg(MSG_SW2_RELEASE);
}//
static void onSw2LongPress() {
	app_sendMsg(MSG_SW2_LONGPRESS);
}//
static void onSw2LongRelease() {
	app_sendMsg(MSG_SW2_LONGRELEASE);
}//

static void onSw3Press(void) {

}//

/***************************************
 *     		   D  A  Q                 *
 ***************************************/
static void onNSweeps(void* this) {
	DAQ_stop(&daq);
	app_sendMsg(MSG_SWEEP_COMPLETED);
	
}//


/*************************************************************************//** 
 * prompt(). Presenta el prompt en la consola.
 * @author      Marcelo A. Valdéz
 * @copyright   FAdeA - Córdoba
 * @related     Application
 ****************************************************************************/
static void prompt() {
	printf(STR_READY);
}//


/* RX RECEIVER */
void onRFStart() {
	printf((frchar*)"\r\nstart detected\r\n");
}//		

void onRFButton() {
	printf((frchar*)"\r\nRF button detected\r\n");
}//

		
/***************************************
 *                                     * 
 *     o n    A S S E R T (  )         *
 *                                     *
 ***************************************/
void onAssert__(char const *file, unsigned line)
{
#ifdef __DEBUG
	printf((frchar*)"\n---- ASSERTION ERROR ----\n\tFILE:\t \"%s\" \n\t"
			  "line:\t %d", file, line);
	while(1);
#endif
}//
