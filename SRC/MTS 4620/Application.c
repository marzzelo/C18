//+------------------------------------------------------------------+
//|       $Workfile:: Application.c              $ $Revision:: 39    $
//+------------------------------------------------------------------+
//|         $Author:: valdez                                         $
//|        $Modtime:: 27/03/12 2:17p                                 $
//|        $Archive:: /@C18/SRC/MTS 4620/Application.c               $
//+------------------------------------------------------------------+
#include "ifcondic.h"
#include "qassert.h"		

#include <p18cxxx.h>
#include <string.h>			
#include <stdlib.h>					
#include <stdio.h>	

#include "fuses.h"
#include "init_pic.h"					
#include "p18fxxx_defs.h" 
#include "typedefs.h"   

#include "xusart.h"
#include "xstrings.h"

#include "CLeds.h"
#include "UartWriter.h"
#include "Reader.h"
#include "CButton.h"
#include "DAQ.h"

#include "application.h"

#include "isr.h"
						

DEFINE_THIS_FILE;

#define DAQBUFF_SIZE 		128
#define READERBUFF_SIZE 	128


#pragma romdata
static far rom const char *cmds[]= {
	"*IDN?",	"*VER?",	"*RST",		"*SET",
	"*ERR?",	"*TST?",	"*CLS",		"*STA",
	"*TSA",		"*TSW",		"*NSA",		"*CHN",
	"*STO",		"*LOA",		"*LIS?",	"*AMP",
	"*ADD",		"#ON",		"#OFF"
};

typedef enum Cmd_ {
	CMD_IDN=0,		CMD_VERSION,	CMD_RESET,		CMD_SETUP,
	CMD_ERROR,		CMD_TEST,		CMD_CLS,		CMD_START,
	CMD_TSAMPLE,	CMD_TSWEEP,		CMD_NSAMPLES,	CMD_CHANNELS,
	CMD_STORE,		CMD_LOAD,		CMD_LIST,		CMD_SETAMP,	
	CMD_ADDRESS,	LATCH_ON,		LATCH_OFF,

	CMDS__MAX
} Cmd;
 
 
#pragma udata
static char cUartBuff_eols[]	= "\0\n\r";  
static frchar delims[]			= " ;";

#pragma udata APPDATA
Application app;

#pragma udata DAQDATA
DAQ daq;
char ans[30];

static char eols[] = "\r\n";	
static char m[20];
static uint8_t tmr;

#pragma udata OUTB
static char outB[READERBUFF_SIZE];		  // para leer string recibido de Reader
#pragma udata

static uint8_t _d;


// para CButtons
static void onSw2Press(void);
static void onSw2Release(void);
static void onSw2LongPress(void);
static void onSw2LongRelease(void);

// para Reader
static void onStringReceived(ReaderRc rc);

// para Application
static void App_run(Application *me);

void sendAns(void);
//void saveEEprom(void);
//void loadEEprom(void);
 
/***************************************
 *                                     * 
 *                                     *
 *                                     *
 ***************************************/
#pragma code ISRH_CODE = 0x08		
void high_vector() {_asm goto ISRH _endasm	} //
#pragma code ISRL_CODE = 0x18
void low_vector() {_asm goto ISRH _endasm	} //
#pragma code


/*==========================================================================*/
void main()	
{   
	InitSFR();
	//printf((frchar*)"---RESET---\n");
	
	App_ctor(&app); 						 //Construye todos los objetos hijos
RUN:
	ClrWdt();
	App_run(&app);
	
	goto RUN;
}
/*==========================================================================*/



void App_run(Application *me)
{
	#define NPARMS 8
	#define ARGLINESIZE 30
	
	char 		argLine[ARGLINESIZE] = {0};
	char 	   *parms[NPARMS];
	uint8_t 	i = 0;
	Cmd 		command; 
	
	
	/* THREAD 0 */
	theUartWriter_update();					 
	
	
	/* THREAD 1 */
	switch(me->_state)
	{
		/////////////////////////////////////////
		case SENDING_START:
		/////////////////////////////////////////
		
			switch (app_getMsg()) 
			{
				/////////////////////////////////////////	
				case SW2_CLICK:
				/////////////////////////////////////////
					app_handled(); 
					break;
					
				/////////////////////////////////////////
				case INCOMMING_MSG:
				/////////////////////////////////////////
					strcpy(argLine, outB);
					
					split(argLine, parms, NPARMS, delims);
					command = strLocate(parms[0], cmds, 0, CMDS__MAX);	
					
					switch (command)
					{
						case LATCH_ON:
							strcpypgm2ram(ans, (frchar*)"LATCH ON!\n");
							DAQ_outputAddress(&daq, 0x00);  // Invese Logic
							sendAns();
							break;
						
						case LATCH_OFF:
							strcpypgm2ram(ans, (frchar*)"LATCH OFF!\n");
							DAQ_outputAddress(&daq, 0xFF);
							sendAns();
							break;
							
							
						case CMD_IDN:
							strcpypgm2ram(ans, (frchar*)"ADAQUS2012\n");
							sendAns();
							break;
							
						case CMD_VERSION:
							strcpypgm2ram(ans, (frchar*)"2.0\n");
							sendAns();
							break;
							
						case CMD_RESET:
							_asm 
								RESET 
							_endasm
							break;			
									
						case CMD_ERROR:
							strcpypgm2ram(ans, (frchar*)DAQ_getError(&daq));
							sendAns();
							break;
							
						case CMD_TEST:
							strcpypgm2ram(ans, (frchar*)"0, Test Passed\n");
							sendAns();
							break;
							
						case CMD_CLS: 
							DAQ_clearBuff(&daq);
							DAQ_stop(&daq);
							break;
							
						case CMD_START:
							DAQ_clearBuff(&daq);
							DAQ_start(&daq);
							break;
							
						case CMD_TSAMPLE:
							DAQ_set_dtSample(&daq, atoi(parms[1]));
							break;			
							
						case CMD_TSWEEP:
							DAQ_set_dtSweep(&daq, atoi(parms[1]));
							break;
							
						case CMD_NSAMPLES:
							DAQ_set_nSamplesPerChannel(&daq, atoi(parms[1]));
							break;
							
						case CMD_CHANNELS:
							DAQ_set_channels(&daq, atoi(parms[1]));
							break;
							
						case CMD_SETAMP:
							DAQ_setAmp(&daq, atoi(parms[1]));
							break;	
							
						case CMD_SETUP:
							{
								uint16_t tSa = atoi(parms[1]);
								uint16_t tSw = atoi(parms[2]);
								uint16_t nSa = atoi(parms[3]);
								uint8_t nCh = atoi(parms[4]);
								
								DAQ_setup(&daq, tSa, tSw, nSa, nCh);
							
								//printf((frchar*)"\r\ntSa,tSw,nSa,nCh=%u,%u,%u,%u\r\n", tSa, tSw, nSa, nCh);
							}
							break;
							
						case CMD_STORE:
							//saveEEprom();
							break;
							
						case CMD_LOAD:
							//loadEEprom();
							break;
							 
						case CMD_LIST:
							sprintf(ans, (frchar*)"%u,%u,%u,%u\n", 
									daq._tBSample._dt,
									daq._tBSweep._dt,
									daq._nSamplesPerChannel,
									daq._nChannels);
							sendAns();
							break;
				
						
							
						case CMD_ADDRESS:
							DAQ_outputAddress(&daq, atoi(parms[1]));
							sprintf(ans, (frchar*)"ADDRESS=%u\n", atoi(parms[1]));
							sendAns();
							break;
							
						default:
							strcpypgm2ram(ans, (frchar*)"ERROR\n");
							sendAns();
							break;
							
					}
					
					app_handled(); 
					break;
									
				}//
				
			}
}//


/***************************************
 *                                     * 
 *       C O N S T R U C T O R         *
 *                                     *
 ***************************************/
void App_ctor(Application *me) {

	/***************************************
	 *                                     * 
	 *     		B U T T O N S              *  
	 *                                     *
	 ***************************************/
	#define PINB 4
	CButton_ctor(&me->_sw2, &PORTB, PINB, 
							onSw2Press, 
							onSw2Release, 
							onSw2LongPress, 
							onSw2LongRelease);
 	

	/***************************************
	 *                                     * 
	 *       U A R T   R E A D E R	       *
	 *                                     *
	 ***************************************/
 	#define TIMEOUT_X10MS 500
	theReader_ctor(			eols, 				// chrs de fin de entrada
							DIM(eols), 			// size of chrs
							TIMEOUT_X10MS, 		// espera maxima
							onStringReceived);	// handler evento FIN DE ETRADA
	
	theReader_start();
	
	
	/***************************************
	 *                                     * 
	 *               D A Q          	   *
	 *                                     *
	 ***************************************/
	 #define DTSAMPLE	100L
	 #define DTSWEEP	3000L
	 #define NSWEEPS	0
	 #define NCHANNELS	1
	 #define TRISAMASK	0b00000001	// RA0
	 
	 
 	DAQ_ctor(	&daq, 
 		
 				DTSAMPLE, 
 				DTSWEEP, 
 	
 				NSWEEPS, 
 				NCHANNELS, 
 				TRISAMASK,
 	
 				VCFG1_VSS,
 				VCFG0_VDD,
 				A2_D11,
 				AD_CH1,
 	
 				&PORTD,
 			 	App_onNSweeps);
	
	/* DEBE CONSTRUIRSE DESPUES DE DAQ, YA QUE UTILIZA SU BUFFER */
	/***************************************
	 *                                     * 
	 *      U A R T   W R I T E R   	   *
	 *                                     *
	 ***************************************/
	theUartWriter_ctor(DAQ_getCBuff(&daq), null);
	theUartWriter_start();
	//CBuff_pushRomString(DAQ_getCBuff(&daq), (frchar*)"\nUART Writer Ready...");	
	
	me->_state = SENDING_START;  							   // estado inicial
	app_handled();

}//


/****************************************************************************
 *                                                                          * 
 *                    E V E N T   H A N D L E R S                           *
 *                                                                          *
 ****************************************************************************

/***************************************
 *                                     * 
 *     C B U T T O N      E. H.        *
 *                                     *
 ***************************************/
void onSw2Press() {
	//theWriter_putrString((frchar*)"\nSW2 Pressed!");
}

void onSw2Release() {
	//theWriter_putrString((frchar*)"\nSW2 Released!\t\t\t<<< CLICK 2 >>>");
	app_sendMsg(SW2_CLICK);
}//
void onSw2LongPress() {
	//theWriter_putrString((frchar*)"\nSW2 LONG Pressed!\t\t\t<<< LONG CLICK 2 >>>");	
}//
void onSw2LongRelease() {
	//theWriter_putrString((frchar*)"\nSW2 LONG Released!");	
}//

/***************************************
 *                                     * 
 *         R E A D E R                 *
 *                                     *
 ***************************************/	
void onStringReceived(ReaderRc rc) {
	theReader_read(outB);	//	--- echo ---
	app_sendMsg(INCOMMING_MSG);
	
	//theWriter_putString(outB);
}//


/***************************************
 *                                     * 
 *              D A Q                  *
 *                                     *
 ***************************************/
void App_onNSweeps(void* this) {
	DAQ_stop(&daq);
}//


void sendAns(void) {
	uint8_t i = 0;
	
	// Copiar la respuesta en el buffer del DAQ para que 
	// sea enviado por el Writer a la UART
	DAQ_clearBuff(&daq);
	CBuff_pushString(DAQ_getCBuff(&daq), ans);
}//

