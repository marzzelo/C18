/*****************************************************************************
* Product: QF/C
* Last Updated for Version: 4.0.00
* Date of the Last Update:  Apr 07, 2008
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2008 Quantum Leaps, LLC. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Alternatively, this software may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GPL and are specifically designed for licensees interested in
* retaining the proprietary status of their code.
*
* Contact information:
* Quantum Leaps Web site:  http://www.quantum-leaps.com
* e-mail:                  info@quantum-leaps.com
*****************************************************************************/
#include "qf_pkg.h"
#include "qassert.h"

Q_DEFINE_THIS_MODULE(qf_pool)

/**
* \file
* \ingroup qf
* \brief QF_pool_[] definition and QF_poolInit() implementation.
*/

/* Package-scope objects ---------------------------------------------------*/
                                  /* MAV: Imprescindible inicializar a 0x00 */
QF_EPOOL_TYPE_ QF_pool_[3] = {0};                 /* allocate 3 event pools */
uint8_t QF_maxPool_ = 0;               /* number of initialized event pools */

/*..........................................................................*/
void QF_poolInit(void *poolSto, uint32_t poolSize, QEventSize evtSize) {


                      /* cannot exceed the number of available memory pools */
/* -------------------------------------------------------------------------
   This precondition (see Chapter 6, “Customized Assertions in C/C++”) 
   asserts that the application does not attempt to initialize more than the 
   supported number of event pools (currently three).
   -------------------------------------------------------------------------*/
    Q_REQUIRE(QF_maxPool_ < (uint8_t)Q_DIM(QF_pool_));
    

	        /* please initialize event pools in ascending order of evtSize: */
/* -------------------------------------------------------------------------
	For possibly quick event allocation, the event pool array QF_pool_[]
	must be sorted in ascending order of block sizes. This precondition asserts
	that the application initializes event pools in the increasing order of the
	event sizes. This assertion significantly simplifies the QF_poolInit()
	function without causing any true inconvenience for the application
	implementer.
   -------------------------------------------------------------------------*/    
    Q_REQUIRE((QF_maxPool_ == (uint8_t)0)
              || (QF_EPOOL_EVENT_SIZE_(QF_pool_[QF_maxPool_ - 1]) < evtSize));
                /* perfom the platform-dependent initialization of the pool */
    QF_EPOOL_INIT_(QF_pool_[QF_maxPool_], poolSto, poolSize, evtSize);
    ++QF_maxPool_;                                         /* one more pool */
}
