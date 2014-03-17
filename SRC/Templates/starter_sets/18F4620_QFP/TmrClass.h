#ifndef TMRCLASS_H_
#define TMRCLASS_H_

#include "typedefs.h"
#include "cplus.h"

CLASS(TMRclass)
	char AvailTimers; /* public */
	int *tArray__;	
	char tmSize__;
	//int tempTd__;
	DWORD tBusy__;
METHODS
	/* Constructor
	 * *tArray: Vector de temporizadores (máx 24 temporizadores)
	 * tmSize: Size del Vector (usar DIM(tA) : (sizeof(array_)/sizeof(*(array_))))
	 * FUNCIÓN: inicializa los campos de la clase
	 */
	TMRclass *TMCtor_(TMRclass *me, int* tArray, char tmSize);
	
	/* Start
	 * t0: Periodo del temporizador solicitado
	 * FUNCIÓN: Arranca un temporizador de la clase y entrega un puntero al mismo
	 */
	int* TMStart(TMRclass *me, int t0);

	/* Free
	 * *t: Puntero al temporizador que desea liberarse
	 * FUNCION: Libera un temporizador de la clase para su posterior utilización 
	 */
	void TMFree(TMRclass *me, int* t);
	
	/* Update
	 * FUNCION: Actualiza todos los temporizadores de la clase.
	 * Tìpicamente, usado dentro de la ISR. Todos los temporizadores tendrán
	 * el mismo periodo de clock.
	 */
	void TMUpdate(TMRclass *me);
END_CLASS


#endif
//

/*********************
 *  EJEMPLO DE USO:
 *********************
 
TMRclass TM;  
int tA[10];
int *T[3];
	
void main(void)
{
	int i;
	
	
	TMCtor_(&TM, tA, DIM(tA));
	for (i = 0; i<10; i++)
		T[i] = TMStart(&TM, i);
		
	TMFree(&TM, T[1]);
	TMFree(&TM, T[5]);
	
	T[2] = TMStart(&TM, 3);
	
	////////////////
	///   ISR    ///
	////////////////
	while(*T[2])
	{
		TMUpdate(&TM);
	}
	
	return;

}
*/
