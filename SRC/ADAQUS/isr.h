//+--------------------------------------------------------+
//| I S R   V E C T O R S                                  |
//+--------------------------------------------------------+

#ifndef _ISR_H
#define _ISR_H

void ISRH(void);    
void ISRL(void);    

// Temporizadores de sistema (deben publicarse para poner a cero en preset)
extern volatile byte 	TMRx10ms; 						///< Contador de 10ms
extern volatile byte 	TMRx100ms;						///< Contador de 100ms
extern volatile byte 	TMRx1s;							///< Contador de 1000ms
extern volatile byte 	TMRx1min;						///< Contador de minutos
extern volatile byte 	TMRx1h;							///< Contador de horas
extern volatile byte 	TMRx1d;							///< Contador de dias

#endif
