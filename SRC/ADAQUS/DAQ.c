//+--------------------------------------------------------------------------+
//|  $Workfile:: DAQ.c                             $ $Revision:: 36          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/12/13 9:23                                                $
//|  $Archive:: /@C18/SRC/ADAQUS/DAQ.c                                       $
//+--------------------------------------------------------------------------+



#include <p18cxxx.h>

#include "p18fxxx_defs.h"
#include "typedefs.h"
#include "xadc.h"
#include "DAQ.h"
#include "Timer.h"
#include "qassert.h"
#include "bitops.h"
#include <stdio.h>	

DEFINE_THIS_FILE;

/*
 dtSample  |<->|                  |<--------dtSweep--------->|
           
_______|育_|育_|育________________|育_|育_|育________________|育_|育_|育_______
	   ch1 ch2 ch3                ch1 ch2 ch3				 ch1 ch2 ch3
	   
	   sweep 1                    sweep 2					 sweep 3 ...
       

*/

#pragma romdata
static rom char *ErrCodes[] = {
	"0,No Errors\n", 
	"1,TSweep Too Short\n",
	"2,TSample is Zero\n",
	"3,No Channels Selected\n",
	"4,Amp Factor Error\n",
	"5,Too many channels\n"
};


// Singleton Definition
#pragma udata DAQDATA
DAQ daq;


static void _onSample(void*);
static void _onNSamples(void*);


DAQ *DAQ_ctor(		DAQ *me, 
				  	uint8_t trisAMask,
					uint8_t VCFG1, 
					uint8_t VCFG0, 
					uint8_t PCFG,
					uint8_t CHS,
					port_t *addressPort,
					port_t *gainPort,
					uint8_t gainBasePin,
					Handler onNSweeps  // se asigna a tBSweep.onTicksDone() [FINAL MUESTREO]
			)
{
	// NOTA: Configurar desde main() el TRIS del puerto addressPort como SALIDAS
	
	// tBSample.onTicksDone <-- null  (nSamples = 0: continuous sampling)
	// tbSweep.onTimeElapsed <-- onNSamples() : reinicia tBSample
	uint8_t key;

	me->_errCode = NO_ERROR;
	
	INT_LOCK(key);
	
	TRISA |= trisAMask; 		    /* AD requires INPUT pin direction */
	PIE1bits.ADIE = 0;			    /* no Habilitar interrupcion AD */	
	me->_flags = SWEEP_ON;
	
	// temporizador para muestras individuales
	#define TBSA_NTICKS   0
	Timer_ctor(&me->_tBSample, 
			   (void*)me,
			   100,	
			   TBSA_NTICKS,
			   _onSample,  
			   null);
			   
	// temporizador para trenes de muestras
	#define TBSW_NTICKS  1
	Timer_ctor(&me->_tBSweep, 
			   (void*)me,
			   3500, 
			   TBSW_NTICKS,
			   _onNSamples,
			   onNSweeps	// <---- USUARIO
			   );	


	// Constructor para el CBuff interno	   
	CBuff_ctor(&me->_cBuff,
				me->_buff, DAQBUFF_SIZE,
				null);

	me->_addressPort = addressPort;
	me->_ADCON0 = CHS;
	me->_ADCON1 = VCFG1 & VCFG0 & PCFG; // VCFG1 & VCFG0 & PCFG;
	me->_ADCON2 = AD_LEFT & ACQT_0 & ADCS_FRC;
	
	me->_gainPort = gainPort;
	me->_gainBasePin = gainBasePin;
	DAQ_setAmp(me, 0);
	
	me->_fromCh = 0;
	me->_toCh = 31;
	
	INT_UNLOCK(key);
	return me;
}//



void DAQ_start(DAQ *me) {
	me->_actChannel = me->_fromCh;		
	Timer_start(&me->_tBSweep);
	Timer_start(&me->_tBSample);
}//

void DAQ_stop(DAQ *me){
	Timer_stop(&me->_tBSweep);
	Timer_stop(&me->_tBSample);
}//

void DAQ_clearBuff(DAQ *me) {
	CBuff_clear(&me->_cBuff);
}

void DAQ_set_dtSample(DAQ *me, uint16_t dt){
	Timer_set_dt(&me->_tBSample, dt);
}//

void DAQ_set_dtSweep(DAQ *me, uint16_t dt){
	Timer_set_dt(&me->_tBSweep, dt);
}//


void DAQ_set_nSamplesPerChannel(DAQ *me, uint16_t nSamplesPerChannel){
	Timer_set_nTicks(&me->_tBSweep, nSamplesPerChannel);
}//


void DAQ_setup(	DAQ *me, 
				uint16_t dtSample, 
				uint16_t dtSweep, 
				uint16_t nSamples, 
				uint8_t from,
				uint8_t to) {

	me->_errCode = NO_ERROR;
	
	Timer_set_dt(&me->_tBSample, dtSample);
	Timer_set_dt(&me->_tBSweep, dtSweep);
	Timer_set_nTicks(&me->_tBSweep, nSamples);
	Timer_set_nTicks(&me->_tBSample, 0);
	
	me->_fromCh = from;
	me->_toCh = to;
	me->_nSamplesPerChannel = nSamples;
}//

	
void DAQ_update(DAQ *me){
	Timer_update(&me->_tBSweep);
	Timer_update(&me->_tBSample);
}//


CBuff *DAQ_getCBuff(DAQ *me) {
	return &me->_cBuff;
}//

void DAQ_copyDataToExternalBuffer(DAQ *me, char *extBuff) {
	CBuff_popString(&me->_cBuff, extBuff);
}//

rom char *DAQ_getError(DAQ *me) {
	ErrCode ec = me->_errCode;
	me->_errCode = NO_ERROR;	// Borrar al leer
	return ErrCodes[ec];
}//



static void _onSample(void* this) {

	DAQ *me = (DAQ*)this;
	uint8_t c = 10;

	TRISA |= me->_trisAMask;
	
	if (me->_flags & SWEEP_ON) {
		DAQ_outputAddress(me, me->_actChannel);	
	}
	
	ADCON1 = me->_ADCON1;
	ADCON0 = me->_ADCON0;
	ADCON0 |= AD_ON;
	
	while (--c);			// Esperar adquisici鏮 
	
	ADCON0bits.GO = 1;		/** - Lanza (Start) CONVERSION */
		
	while (ADCON0bits.GO)
		ClrWdt();			// Esperar a que termine conversi鏮
		
	CBuff_push(&me->_cBuff, ADRESL);
	CBuff_push(&me->_cBuff, ADRESH);
			
	ADCON0 = AD_OFF;
		
	if (++me->_actChannel > me->_toCh) {
		me->_actChannel = me->_fromCh;
		// No quedan canales para muestrear, esperar siguiente barrido
		Timer_stop(&me->_tBSample);			
		return;
	}
}//


void DAQ_sample(DAQ* me, uint8_t add) {
	uint8_t c = 100;

	TRISA |= me->_trisAMask;
	
	DAQ_outputAddress(me, add);	
	
	ADCON1 = me->_ADCON1;
	ADCON0 = me->_ADCON0;
	ADCON0 |= AD_ON;
	
	while (--c);			// Esperar adquisici鏮 
	
	ADCON0bits.GO = 1;		/** - Lanza (Start) CONVERSION */
		
	while (ADCON0bits.GO)
		ClrWdt();			// Esperar a que termine conversi鏮
		
	CBuff_push(&me->_cBuff, ADRESL);
	CBuff_push(&me->_cBuff, ADRESH);
			
	ADCON0 = AD_OFF;
}//



static void _onNSamples(void* this) {
	DAQ *me = (DAQ*)this;
	
	// s鏊o lanzar siguiente barrido
	Timer_start(&me->_tBSample);
}//

	
/** todo	EXTENDER CLASE CON Amp y Address */	
void DAQ_outputAddress(DAQ *me, uint8_t add) {
	uint8_t addmask = *me->_addressPort & 0b11100000;  	// xxx0 0000
	
	addmask |= add;										// xxxA AAAA
	*me->_addressPort = addmask;
}//

void DAQ_setAmp(DAQ *me, uint8_t ampFactor) {
	uint8_t ampmask = *me->_gainPort & ~(0b00000111 << me->_gainBasePin);  // 000x xxxx
	
	ampmask |= (ampFactor << me->_gainBasePin);  // FFFx xxxx
	*me->_gainPort = ampmask;
}//	


void DAQ_setFlags(DAQ *me, uint8_t mask) {
	me->_flags |= mask;
}

void DAQ_resetFlags(DAQ *me, uint8_t mask) {
	me->_flags &= ~mask;
}



