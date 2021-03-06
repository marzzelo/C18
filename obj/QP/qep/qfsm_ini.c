/*****************************************************************************
* Product: QEP/C
* Last Updated for Version: 4.0.00
* Date of the Last Update:  Apr 05, 2008
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
#include "qep_pkg.h"
#include "qassert.h"

Q_DEFINE_THIS_MODULE(qfsm_ini)

/**
* \file
* \ingroup qep
* \brief QFsm_init() implementation.
*/

/*..........................................................................*/
void QFsm_init(QFsm *me, QEvent const *e) {
    QS_INT_LOCK_KEY_

    QS_BEGIN_(QS_QEP_STATE_INIT, QS_smObj_, me)
        QS_OBJ_(me);                           /* this state machine object */
        QS_FUN_((QStateHandler)0);    /* the source (not defined for a FSM) */
        QS_FUN_(me->state);                 /* the target of the transition */
    QS_END_()

                                 /* execute the top-most initial transition */
    Q_ALLEGE((*me->state)(me, e) == Q_RET_TRAN);/* transition must be taken */

    (void)QEP_TRIG_(me->state, Q_ENTRY_SIG);            /* enter the target */

    QS_BEGIN_(QS_QEP_INIT_TRAN, QS_smObj_, me)
        QS_TIME_();                                           /* time stamp */
        QS_OBJ_(me);                           /* this state machine object */
        QS_FUN_(me->state);                         /* the new active state */
    QS_END_()
}
