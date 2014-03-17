/********************************************************************
 * Quantum Assertions--Design by Contract(TM of ISI) facilities
 * Copyright (c) 2002 Miro Samek, Palo Alto, CA.
 * All Rights Reserved.
 *******************************************************************/
/*
	USO: 
		1) Llamar a la macro DEFINE_THIS_FILE al comienzo del archivo
		2) Definir NASSERT si se desea deshabilitar los ASSERTS
		3) Definir la función onAssert__() que se ejecutará cuando
		   falle una aserción (ver declaración aquí)
		4) Llamar al macro ASSERT(), REQUIRE(), ENSURE(), INVARIANT() o 
		   ALLEGE() cuando sea necesario 
		NOTA: El argumento de estas funciones debe ser Booleano, y
		      produce los efectos secundarios correspondientes
		NOTA: Este header no tiene módulo fuente asociado.
*/
#ifndef qassert_h
#define qassert_h

/** NASSERT macro disables all contract validations
 * (assertions, preconditions, postconditions, and invariants).
 */  
#ifndef NASSERT 
                  /* callback invoked in case of assertion failure */
extern void onAssert__(char const *file, unsigned line);


#define DEFINE_THIS_FILE \
   static const char THIS_FILE__[] = __FILE__

#define ASSERT(test_)\
   if (test_) {      \
   }                 \
   else onAssert__(THIS_FILE__, __LINE__)

#define REQUIRE(test_)   ASSERT(test_)
#define ENSURE(test_)    ASSERT(test_)
#define INVARIANT(test_) ASSERT(test_)
#define ALLEGE(test_)    ASSERT(test_)

#else                                           /* #ifndef NASSERT */

#define DEFINE_THIS_FILE extern const char THIS_FILE__[]
#define ASSERT(test_)    
#define REQUIRE(test_)   
#define ENSURE(test_)    
#define INVARIANT(test_) 
#define ALLEGE(test_)\
   if (test_) {      \
   }                 \
   else

#endif

#endif                                                /* qassert_h */
