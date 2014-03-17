//+--------------------------------------------------------------------------+
//|  $Workfile:: DAQ.c                             $ $Revision:: 31          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/04/12 1:24p                                               $
//|  $Archive:: /@C18/SRC/Explorer1/DAQ.c                                    $
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

#pragma udata

static void _onSample(void*);
static void _onNSamples(void*);


DAQ *DAQ_ctor(		DAQ *me, 
				  	uint16_t dtSample, 
				  	uint16_t dtSweep,
				  	uint16_t nSamplesPerChannel,
				  	uint8_t nChannels,
				  	uint8_t trisAMask,
					uint8_t VCFG1, 
					uint8_t VCFG0, 
					uint8_t PCFG,
					uint8_t CHS,
					port_t *addressPort,
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
	Timer_ctor(&me->_tBSample, 
			   (void*)me,
			   dtSample,	
			   0,
			   _onSample,  
			   null);
			   
	// temporizador para trenes de muestras
	Timer_ctor(&me->_tBSweep, 
			   (void*)me,
			   dtSweep, 
			   nSamplesPerChannel,
			   _onNSamples,
			   onNSweeps	// <---- USUARIO
			   );	


	// Constructor para el CBuff interno	   
	CBuff_ctor(&me->_cBuff,
				me->_buff, DAQBUFF_SIZE,
				null);

	DAQ_setAmp(me, 0);
	me->_nChannels = nChannels;
	me->_nSamplesPerChannel = nSamplesPerChannel;
	
	me->_addressPort = addressPort;
	me->_ADCON0 = CHS;
	me->_ADCON1 = VCFG1 & VCFG0 & PCFG; // VCFG1 & VCFG0 & PCFG;
	me->_ADCON2 = AD_LEFT & ACQT_0 & ADCS_FRC;
	
	INT_UNLOCK(key);
	return me;
}//


void DAQ_start(DAQ *me) {
	me->_actChannel = 0;		// comenzar el barrido siempre con canal #0
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

void DAQ_set_channels(DAQ *me, uint8_t nChannels) {
	me->_nChannels = nChannels;
}//


void DAQ_setup(	DAQ *me, 
				uint16_t dtSample, 
				uint16_t dtSweep, 
				uint16_t nSamples, 
				uint8_t nChannels) {

	me->_errCode = NO_ERROR;
	if ((dtSample*nChannels >= dtSweep) || (dtSweep == 0)) {
		me->_errCode = TSWEEP_TOO_SHORT;
		return;
	}
	if (nChannels == 0) {
		me->_errCode = NO_CHANNELS_SELECTED;
		return;
	}
	if (nChannels > 32) {
		me->_errCode = TOO_MANY_CHANNELS;
		return;
	}
	if (dtSample == 0) {
		me->_errCode = TSAMPLE_IS_ZERO;
		return;
	}
	
	Timer_set_dt(&me->_tBSample, dtSample);
	Timer_set_dt(&me->_tBSweep, dtSweep);
	Timer_set_nTicks(&me->_tBSweep, nSamples);
	Timer_set_nTicks(&me->_tBSample, 0);
	me->_nChannels = nChannels;
	me->_actChannel = 0;
	me->_nSamplesPerChannel = nSamples;
}//

	
void DAQ_update(DAQ *me){
	Timer_update(&me->_tBSweep);
	Timer_update(&me->_tBSample);
}//



CBuff *DAQ_getCBuff(DAQ *me) {
	return &me->_cBuff;
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
		
	CBuff_push(&me->_cBuff, ADRESH);
	CBuff_push(&me->_cBuff, ADRESL);
			
	ADCON0 = AD_OFF;
		
	if (++me->_actChannel >= me->_nChannels) {
		me->_actChannel = 0;
		// No quedan canales para muestrear, esperar siguiente barrido
		Timer_stop(&me->_tBSample);		
		return;
	}
}//



static void _onNSamples(void* this) {
	DAQ *me = (DAQ*)this;
	
	// s鏊o lanzar siguiente barrido
	Timer_start(&me->_tBSample);
}//

	
/** todo	EXTENDER CLASE CON Amp y Address */	
void DAQ_outputAddress(DAQ *me, uint8_t add) {
	*me->_addressPort = add;
}//


void DAQ_setAmp(DAQ *me, uint8_t ampFactor) {
//	if (ampFactor > 7) {
//		me->_errCode = AMP_FACTOR_ERROR;
//		return;
//	}
//	me->_ampFactor = ampFactor;	
//	iAMP &= 0b00011111;
//	iAMP |= (ampFactor << 5);
}//

void DAQ_setFlags(DAQ *me, uint8_t mask) {
	me->_flags |= mask;
}

void DAQ_resetFlags(DAQ *me, uint8_t mask) {
	me->_flags &= ~mask;
}



