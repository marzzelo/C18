#include "typedefs.h"  								      /* DWORD */
#include "Qassert.h"								   /* ASSERT() */
#include "string.h"  							       /* memset() */
#include "bitops.h"                              /* bitgetdw() ... */
#include "TmrClass.h" 
#include <stdio.h>


DEFINE_THIS_FILE; // Usado por ASSERT()

/* Constructor
 * *tArray: Vector de temporizadores (máx 24 temporizadores)
 * tmSize: Size del Vector (usar DIM(tA) : (sizeof(array_)/sizeof(*(array_))))
 * FUNCIÓN: inicializa los campos de la clase
 */
TMRclass *TMCtor_(TMRclass *me, int* tArray, char tmSize)
{
	ASSERT(tmSize <= 24);
	me->tArray__ = tArray;
	me->tmSize__ = tmSize;
	memset(me->tArray__, 0x00, tmSize);
	me->tBusy__._dword = 0x00000000;
	me->AvailTimers = tmSize; /* tmSize está en bytes, cada timer es int */
#ifdef __DEBUG
	printf((frchar*)"\nTMCtor: AvailTimers = %d", me->AvailTimers);
#endif
	ASSERT((me->AvailTimers >= 0) && (me->AvailTimers <= me->tmSize__));
	return me;
}//

/* Start
 * t0: Periodo del temporizador solicitado
 * FUNCIÓN: Arranca un temporizador de la clase y entrega un puntero al mismo
 */
int *TMStart(TMRclass *me, int t0)
{
	char i;
	
	for (i = 0; i < 8*sizeof(DWORD); i++)
	{
		DWORD tb = bitgetdw(&me->tBusy__, i);
		if (tb._dword == 0x00000000)
		{
			me->tArray__[i] = t0;
			bitsetdw(&me->tBusy__, i);
			--me->AvailTimers;
#ifdef __DEBUG
			printf((frchar*)"\nTMStart: AvailTimers = %d", me->AvailTimers);
#endif		
			ASSERT((me->AvailTimers >= 0) && (me->AvailTimers <= me->tmSize__));
			return &me->tArray__[i];
		}
	}
	return 0; // Todos ocupados
}//


/* Free
 * *t: Puntero al temporizador que desea liberarse
 * FUNCION: Libera un temporizador de la clase para su posterior utilización 
 */
void TMFree(TMRclass *me, int* t)
{
	*t = 0x00;
	bitresetdw(&me->tBusy__, (t - me->tArray__));
	++me->AvailTimers;
#ifdef __DEBUG
	printf((frchar*)"\nTMFree: AvailTimers = %d", me->AvailTimers);
#endif
	ASSERT((me->AvailTimers >= 0) && (me->AvailTimers <= me->tmSize__));
}//	
	
	
/* Update
 * FUNCION: Actualiza todos los temporizadores de la clase.
 * Tìpicamente, usado dentro de la ISR. Todos los temporizadores tendrán
 * el mismo periodo de clock.
 */
void TMUpdate(TMRclass *me)
{
	unsigned char i;
	
	for (i = 0; i < me->tmSize__; i++)
		if (me->tArray__[i] != 0)
			me->tArray__[i]--;
}//	

