//+--------------------------------------------------------------------------+
//|  $Workfile:: DAQ.h                             $ $Revision:: 29          $
//+--------------------------------------------------------------------------+
//|  $Author:: valdez                                                        $
//|  $Modtime:: 12/12/13 8:42                                                $
//|  $Archive:: /@C18/SRC/ADAQUS/DAQ.h                                       $
//+--------------------------------------------------------------------------+
//! \file DAQ.h
//! \brief Muestrea hasta 32 canales anal�gicos y los almacena en un \ref cBuff

#ifndef DAQ_H_
#define DAQ_H_

#include "p18fxxx_defs.h"
#include "typedefs.h"
#include "Timer.h"
#include "CBuff.h"

#define DAQBUFF_SIZE 128

typedef enum ErrCode_ {
	NO_ERROR = 0,
	TSWEEP_TOO_SHORT,
	TSAMPLE_IS_ZERO,
	NO_CHANNELS_SELECTED,
	AMP_FACTOR_ERROR,
	TOO_MANY_CHANNELS
} ErrCode;


/*************************************************************************//** 
 * Muestrea hasta 32 canales externos anal�gicos.
 * @li Almacena las muestras en un \ref cBuff (buffer circular) con un periodo 
 * de muestreo establecido a trav�s de un \ref TBase componente. 
 * @li Permite configurar el TRIS del puerto de entrada mediante el callback onSetup.
 * @li Genera eventos al concluir cada muestra y al muestrear todos los canales
 * tras cada periodo de muestreo. 
 * @li Se puede fijar el n�mero de muestras total por canal.
 * @note		_buff es un buffer lineal (char[n]) de uso interno, creado
 *				automaticamente al instanciar el DAQ. En este buffer se depositan
 *				cada una de las muestras tomadas.
 *				*_outBuff es un puntero a un buffer externo, especificado en el
 *				constructor, donde se copiar�n las muestras en batch
 * @author      Marcelo A. Vald�z
 * @copyright   <b>FAdeA</b> C�rdoba
 ****************************************************************************/
 
/* FLAGS */
#define SWEEP_ON	(1 << 0)

 
CLASS(DAQ)
	Timer _tBSample;			///< Genera evento para muestrear UN CANAL
	Timer _tBSweep;				///< Base de tiempos para cada barrido de N CANALES
	uint16_t _nSamplesPerChannel;	///< Cantidad de muestras a tomar (0 = muestreo continuo)
	
	CBuff _cBuff;				///< Buffer circular para depositar las muestras
	char _buff[DAQBUFF_SIZE];	///< buffer lineal para el buffer circular
	
	uint8_t _actChannel;		///< canal que est� siendo muestreado
	uint8_t _ampFactor;			///< Factor de amplificacion
	uint8_t _ADCON0;			///< Registros de configuraci�n
	uint8_t _ADCON1;			///< Registros de configuraci�n
	uint8_t _ADCON2;			///< Registros de configuraci�n
	uint8_t _trisAMask;			///< Configuraci�n TRISA (se aplica bitOR)
	port_t *_addressPort;		///< Puerto de direccionamiento (multiplexor)
	port_t *_gainPort;			///< Puerto donde se conecta el Amp gain control
	uint8_t _gainBasePin;		///< Pin base para el gain control (3 pines)
	uint8_t _address;			///< Direcci�n actual para el multiplexor
	uint8_t _fromCh;			///< Canal inicial de barrido 
	uint8_t _toCh;				///< Canal final de barrido 
	ErrCode _errCode;			///< Error Code
	uint8_t _flags;				///< Flags
	
METHODS


/*************************************************************************//** 
 * Constructor de la clase. 
 * @param[in]    me			puntero a este objeto
 * @param[in]    dtSample			dt entre muestras de distintos canales
 * @param[in]    dtSweep		Periodo de muestreo (mismo canal)
 * @param[in]    nSamplesPerChannel		Samples per channel (0 = continuo)
 * @param[in]    nChannels		Cantidad de canales a muestrear (#0, #1,.. #nChannels-1)
 * @param[in]    trisAMask		mascara binaria de pines anal�gicos (PORTA unicamente)
 * @param[in]    VSS_REF		Referencia positiva 
 * @param[in]    VDD_REF		Periodo de muestreo
 * @param[in]    PIN_CONFIG		Samples per channel
 * @param[in]    CHS			Canal �nico por donde se muestrea la se�al
 * @param[in]    AddressPort	Puerto de Direccion para Seleccion de canal
 * @param[in]    onSweep		Controlador de evento barrido completado
 * @param[in]    onNSweeps		Controlador de evento nSamples completados 
 *								(generalmente llama a DAQ_stop())
 *
 * @returns      Puntero al objeto 
 * @code         C�digo de prueba   
  
	 #define DTSAMPLE	0
	 #define DTSWEEP	100
	 #define NSAMPLES	0
	 #define NCHANNELS	1
	 #define TRISAMASK	0b00000001	// RA0
     DAQ_ctor(	&daq, 
 				DTSAMPLE, 	DTSWEEP, 
 				NSAMPLES, 	NCHANNELS, 
 				TRISAMASK, 
 				VCFG1_VSS, 	VCFG0_VDD,
 				A1_D15, 	AD_CH0, 
 				&PORTD,
 			 	App_onDaqEnd);
 * @endcode
 * @note		 Para adquisici�n continua, nSamplesPerChannel = 0
 * @related		 DAQ
 ****************************************************************************/
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
			);
				  
/*************************************************************************//** 
 * Saca por el puerto _addressPort la direcci�n del canal a muestrear
 * @param[in]    me			This
 * @related		 DAQ
 ****************************************************************************/						  
	void DAQ_outputAddress(DAQ *me, uint8_t add);

/*************************************************************************//** 
 * Inicia el muestreo. Al finalizar cada periodo, genera el evento
 * onChannelSampleReady.
 * @param[in]    me			This
 * @code         C�digo de prueba    
 *				 DAQ_start(&myDAQ);
 * @endcode
 * @related		 DAQ
 ****************************************************************************/						  
	void DAQ_start(DAQ *me);

/*************************************************************************//** 
 * Detiene el muestreo. No se genera el evento onChannelSampleReady.
 * @param[in]    me			This
 * @code         C�digo de prueba    
 *				 DAQ_stop(&myDAQ);
 * @endcode
 * @related		 DAQ
 ****************************************************************************/
	void DAQ_stop(DAQ *me);
	
/*************************************************************************//** 
 * Limpia el buffer del DAQ, rellenandolo con 0x00
 * @param[in]    me			This
 * @code         C�digo de prueba    
 *				 DAQ_clearBuff(&myDAQ);
 * @endcode
 * @related		 DAQ
 ****************************************************************************/
	void DAQ_clearBuff(DAQ *me);
	
/*************************************************************************//** 
 * Especifica el periodo de muestreo
 * @param[in]    me			This
 * @param[in]    dt			periodo de muestreo en [ms] (debe ser superior al n�mero 
 *  						de canales activos por el tiempo de adquisici�n m�s
 *							el tiempo de conversi�n). 
 * @code         C�digo de prueba    
 *				 DAQ_set_dt(&myDAQ, 100);
 * @endcode
 * @related		 DAQ
 ****************************************************************************/	
	void DAQ_set_dtSweep(DAQ *me, uint16_t dt);

/*************************************************************************//** 
 * Especifica el shift entre canales para un mismo muestreo cuasi-simultaneo
 * @param[in]    me			This
 * @param[in]    dt			t shift entre canales
 * @code         C�digo de prueba    
 *				 DAQ_set_dt(&myDAQ, 100);
 * @endcode
 * @related		 DAQ
 ****************************************************************************/	
	void DAQ_set_dtSample(DAQ *me, uint16_t dt);

/*************************************************************************//** 
 * Especifica el n�mero de muestras por canal a adquirir. Para realizar 
 * adquisici�n cont�nua, pasar 0 como nTicks.
 * @param[in]    me			This
 * @param[in]    nSamplesPerChannel	Cantidad de muestras por canal a tomar 
 * @code         C�digo de prueba    
 *				 DAQ_set_nSamplesPerChannel(&myDAQ, 0);
 * @endcode
 * @note		 Para realizar adquisici�n cont�nua, pasar 0 como nTicks
 * @related		 DAQ
 ****************************************************************************/	
	void DAQ_set_nSamplesPerChannel(DAQ *me, uint16_t nSamplesPerChannel);
	
/*************************************************************************//** 
 * Muestrea los canales activos (un canal activo por llamada). Al ingresar a la
 * funci�n saltea los canales no activos hasta encontrar el primer canal activo;
 * luego de tomar la muestra de 10 bits, env�a (push) los dos bytes ADRESH y 
 * ADRESL al puerto serial. Esta funci�n es llamada cada tSample [ms] para
 * muestrear cada uno de los canales activos.
 * Al llegar al canal 31, esta funci�n detiene el temporizador tBSample, 
 * que se volver� a iniciar transcurridos tSweep [ms].
 * @related		 DAQ 
 ****************************************************************************/
	void DAQ_sample(DAQ *me, uint8_t add);
	
/*************************************************************************//** 
 * Actualiza el contador interno de tiempo de muestreo. Debe correr en ISR cada 1ms
 * @param[in]    me			This
 * @note		 Los controladores de evento son llamados desde foreground (ISR)
 *				 por lo que <b>no pueden contener instrucciones printf() ni operaciones
 *				 que requieran tiempos cercanos a 1ms</b>
 * @related		 DAQ
 ****************************************************************************/	
	void DAQ_update(DAQ *me);
	
/*************************************************************************//** 
 * Obtiene el Buffer Circular interno, para SOLO lectura de datos.
 * @returns     Buffer circular interno
 * @related     DAQ
 ****************************************************************************/
	CBuff *DAQ_getCBuff(DAQ *me);
	
/*************************************************************************//** 
 * Copia el buffer interno en un buffer externo especificado
 * @returns     void
 * @related     DAQ
 ****************************************************************************/	
	void DAQ_copyDataToExternalBuffer(DAQ *me, char *extBuff);

	
/*************************************************************************//** 
 * Modifica varias propiedades del objeto DAQ establecidas inicialmente en el ctor.
 * @param[in]    me			This
 * @param[in]    from		Canal inicial de barrido
 * @param[in]    to			Canal final de barrido
 * @related		 DAQ
 ****************************************************************************/	
	void DAQ_setup(	DAQ *me, 
				uint16_t dtSample, 
				uint16_t dtSweep, 
				uint16_t nSamples, 
				uint8_t from,
				uint8_t to);

/*************************************************************************//** 
 * Fija el factor de amplificaci�n del amplificador de instrumentaci�n.
 * El amplificador dipone de 8 niveles, controlados por un registro de 3 bits.
 * @param[in]    ampFactor	factor de amplificaci�n (entre 0 y 7)
 ****************************************************************************/
	void DAQ_setAmp(DAQ *me, uint8_t ampFactor);
	
/*************************************************************************//** 
 * Obtiene el string de error (incluye el c�digo de error)
 * @param[in]    me			This
 * @related		 DAQ
 ****************************************************************************/	
	rom char *DAQ_getError(DAQ *me);
	
	void DAQ_setFlags(DAQ *me, uint8_t mask);
	void DAQ_resetFlags(DAQ *me, uint8_t mask);
	
END_CLASS


// Singleton declaration
extern DAQ daq;

#endif
//



