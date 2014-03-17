/*****************************************************************************
* Product:  QF/C
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
#ifndef qpset_h
#define qpset_h

/**
* \file
* \ingroup qf qk
* \brief platform-independent priority sets of 8 or 64 elements.
*
* This header file must be included in those QF ports that use the
* cooperative "vanilla" kernel or the QK preemptive kernel.
*/

/****************************************************************************/
/** \brief Priority Set of up to 8 elements for building various schedulers
*
* The priority set represents the set of active objects that are ready to
* run and need to be considered by scheduling processing. The set is capable
* of storing up to 8 priority levels.
*
* The priority set allows to build cooperative multitasking schedulers
* to manage up to 8 tasks.
*/
typedef struct QPSet8Tag {
    uint8_t bits;       /**< \brief bimask representing elements of the set */
} QPSet8;

/** \brief the macro evaluates to TRUE if the priority set \a me has elements
*/
#define QPSet8_isEmpty(me_) ((me_)->bits == (uint8_t)0)

/** \brief the macro evaluates to TRUE if the priority set \a me is empty
*/
#define QPSet8_notEmpty(me_) ((me_)->bits != (uint8_t)0)

/** \brief the macro evaluates to TRUE if the priority set \a me_
* has element \a n_.
*/
#define QPSet8_hasElement(me_, n_) \
    (((me_)->bits & Q_ROM_BYTE(QF_pwr2Lkup[n_])) != 0)

/** \brief insert element \a n_ into the set \a me_, n_= 1..8
*/
#define QPSet8_insert(me_, n_) \
    ((me_)->bits |= Q_ROM_BYTE(QF_pwr2Lkup[n_]))

/** \brief remove element n_ from the set \a me_, n_= 1..8
*/
#define QPSet8_remove(me_, n_) \
    ((me_)->bits &= Q_ROM_BYTE(QF_invPwr2Lkup[n_]))

/** \brief find the maximum element in the set, and assign it to n_,
* \note the set cannot be empty
*/
#define QPSet8_findMax(me_, n_) \
    ((n_) = Q_ROM_BYTE(QF_log2Lkup[(me_)->bits]))


/****************************************************************************/
/** \brief Priority Set of up to 64 elements for building various schedulers
*
* The priority set represents the set of active objects that are ready to
* run and need to be considered by scheduling processing. The set is capable
* of storing up to 64 priority levels.
*
* The priority set allows to build cooperative multitasking schedulers
* to manage up to 64 tasks. It is also used in the Quantum Kernel (QK)
* preemptive scheduler.
*/
typedef struct QPSet64Tag {

    /** \brief condensed representation of the priority set
    *
    * Each bit in the bytes attribute represents a byte (8-bits)
    * in the bits[] array. More specifically: \n
    * bit 0 in bytes is 1 when any bit in bits[0] is 1 \n
    * bit 1 in bytes is 1 when any bit in bits[1] is 1 \n
    * bit 2 in bytes is 1 when any bit in bits[2] is 1 \n
    * bit 3 in bytes is 1 when any bit in bits[3] is 1 \n
    * bit 4 in bytes is 1 when any bit in bits[4] is 1 \n
    * bit 5 in bytes is 1 when any bit in bits[5] is 1 \n
    * bit 6 in bytes is 1 when any bit in bits[6] is 1 \n
    * bit 7 in bytes is 1 when any bit in bits[7] is 1 \n
    */
    uint8_t bytes;

    /** \brief Bitmasks representing elements in the set. Specifically: \n
    * bits[0] represent elements 1..8   \n
    * bits[1] represent elements 9..16  \n
    * bits[2] represent elements 17..24 \n
    * bits[3] represent elements 25..32 \n
    * bits[4] represent elements 33..40 \n
    * bits[5] represent elements 41..48 \n
    * bits[6] represent elements 49..56 \n
    * bits[7] represent elements 57..64 \n
    */
    uint8_t bits[8];
} QPSet64;

/** \brief the macro evaluates to TRUE if the priority set \a me has elements
*/
#define QPSet64_isEmpty(me_) ((me_)->bytes == (uint8_t)0)

/** \brief the macro evaluates to TRUE if the priority set \a me is empty
*/
#define QPSet64_notEmpty(me_) ((me_)->bytes != (uint8_t)0)

/** \brief the macro evaluates to TRUE if the priority set \a me_
* has element \a n_.
*/
#define QPSet64_hasElement(me_, n_) \
    (((me_)->bits[Q_ROM_BYTE(QF_div8Lkup[n_])] \
      & Q_ROM_BYTE(QF_pwr2Lkup[Q_ROM_BYTE(QF_div8Lkup[n_]) + 1])) != 0)

/** \brief insert element \a n_ into the set \a me_, n_= 1..64
*/
#define QPSet64_insert(me_, n_) do { \
    (me_)->bits[Q_ROM_BYTE(QF_div8Lkup[n_])]|= Q_ROM_BYTE(QF_pwr2Lkup[n_]);\
    (me_)->bytes |= Q_ROM_BYTE(QF_pwr2Lkup[Q_ROM_BYTE(QF_div8Lkup[n_])+1]);\
} while(0)

/** \brief remove element n_ from the set \a me_, n_= 1..64
*/
#define QPSet64_remove(me_, n_) do { \
    (me_)->bits[Q_ROM_BYTE(QF_div8Lkup[n_])] &= \
        Q_ROM_BYTE(QF_invPwr2Lkup[n_]); \
    if ((me_)->bits[Q_ROM_BYTE(QF_div8Lkup[n_])] == (uint8_t)0) { \
        (me_)->bytes &= \
            Q_ROM_BYTE(QF_invPwr2Lkup[Q_ROM_BYTE(QF_div8Lkup[n_]) + 1]); \
    } \
} while(0)

/** \brief find the maximum element in the set, and assign it to n_,
* \note the set cannot be empty
*/
#define QPSet64_findMax(me_, n_) do { \
    (n_) = (uint8_t)(Q_ROM_BYTE(QF_log2Lkup[(me_)->bytes]) - 1); \
    (n_) = (uint8_t)(((n_)<<3) + Q_ROM_BYTE(QF_log2Lkup[(me_)->bits[n_]]));\
} while(0)

#endif                                                           /* qpset_h */

