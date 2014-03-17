/**********************************************************************
*    Processor:      P18F4550                                         *
*    Description:    ANALOG / DIGITAL module control header           *
**********************************************************************/

// Written By: Marcelo Valdéz, DOBA Embedded Systems
// MPLAB-C18 compliler ver. 3.00 (demo)
//
// Revision History
// 25-06-06		Version inicial

#ifndef _XADC_H
#define _XADC_H


/*******************************************************************************
 *                                   18F4550                                   *
 *******************************************************************************/
#if defined(__18F4550)

	typedef union {				// used by ReadADC()
	int INT;
	struct {
		char LSB;
		char MSB;
	};
} ADResult;					

int ReadADC( void );	// This routine reads the ADRESL and ADRESH and returns these as a long.
							// Es obligatorio especificar (void) en la declaracion!!

#define OpenAD(CHSEL)		ADCON0 = ((CHSEL) << 2) | 0x01	// enables AD module and selects a channel. 
															// CHSEL in [0..12] 
#define BusyAD( ) 			ADCON0bits.GO					// tests ADC conversion status 

#define ConvertAD( )		ADCON0bits.GO = 1  				// Set the GO bit to start a conversion 

// This macro disables AD module & interrupt
#define CloseAD( )  		ADCON0bits.ADON = 0; \
							PIE1bits.ADIE = 0				


/*******************************************************************************
 *                                   18F452                                    *
 *******************************************************************************/
#elif defined(__18F452)


typedef union 
{				
	int INT;
	struct {
		char LSB;
		char MSB;
	};
} ADResult;		
			

int ReadADC( void );	// This routine reads the ADRESL and ADRESH and returns these as a long.

#define OpenAD(CHSEL)		ADCON0 = ((CHSEL) << 3) | 0x01	// enables AD module and selects a channel. 
															// CHSEL in [0..12] 
#define BusyAD( ) 			ADCON0bits.GO					// tests ADC conversion status 

#define ConvertAD( )		ADCON0bits.GO = 1  				// Set the GO bit to start a conversion 

// This macro disables AD module & interrupt
#define CloseAD( )  		ADCON0bits.ADON = 0; \
							PIE1bits.ADIE = 0				



/*******************************************************************************
 *                                   18F4520                                   *
 *******************************************************************************/
#elif (defined(__18F4520) || defined(__18F4620) || defined(__18F4685))


typedef union 
{				
	int INT;
	struct {
		char LSB;
		char MSB;
	};
} ADResult;		
			

int ReadADC(void);				// This routine reads the ADRESL and ADRESH and returns these as a long.

#define OpenAD(CHSEL)		ADCON0 = ((CHSEL) << 2) | 0x01	// enables AD module and selects a channel. 
															// CHSEL in [0..12] 
#define BusyAD( ) 			ADCON0bits.GO					// tests ADC conversion status 

#define ConvertAD( )		ADCON0bits.GO = 1  				// Set the GO bit to start a conversion 

// This macro disables AD module & interrupt
#define CloseAD( )  		ADCON0bits.ADON = 0; \
							PIE1bits.ADIE = 0				
 
/*--------------------------------------------------------------------------*/
#define AD_setPinsAndRefs(VSS_REF, VDD_REF, PIN_CONFIG)		ADCON1 = (VSS_REF) & (VDD_REF) & (PIN_CONFIG)
#define AD_selectChannel(CH)	ADCON0 = ((CH) << 2)			// Channel select
#define AD_clockOn( )			ADCON2 = ACQT_0 & ADCS_FRC		// ACT = Automatic, Clock = int RC
#define AD_on( )				ADCON0bits.ADON = 1		
#define AD_start( )				ADCON0bits.GO = 1				// starts conversion
#define AD_isBusy( ) 			ADCON0bits.GO					// tests ADC conversion status 
#define AD_waitAdResult( )		while(AD_isBusy( )) ClrWdt()	// waits for ADC completion
#define AD_getResult( )			ReadADC()						// This routine reads the ADRESL and ADRESH and returns these as a long.
#define AD_off( )				CloseAD()


#endif	//#ifndef _XADC_H

