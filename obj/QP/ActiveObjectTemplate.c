//+--------------------------------------------------------------------------+
//|  $Workfile:: ActiveObjectTemplate.c                  $ $Revision:: 2     $
//+--------------------------------------------------------------------------+
//|  $Author:: Marcelo                                                       $
//|  $Modtime:: 20/07/09 9:44p                                               $
//|  $Archive:: /@CODE/SRC/QP2_LEARN/ActiveObjectTemplate.c                  $
//+--------------------------------------------------------------------------+
/*************************************************************************//**
@file 	<nombre de este archivo>
@brief	<descripción breve>. <Descripción detallada...>                       
 ****************************************************************************/
#include <p18cxxx.h>
#include <typedefs.h>
#include <stdio.h>
#include <string.h>
#include "bsp.h"			                   
#include "signals.h"

Q_DEFINE_THIS_FILE

/*************************************************************************//**
Evento: <nombre del evento>
@param[in,out] sig  Señales: <SEÑAL1>_SIG, <SEÑALn>_SIG
 ****************************************************************************/
typedef struct <#nombre>Evt_Tag {
	QEvent super;                                           /**< Clase base */
} <#nombre>Evt; /* Private */

/*  Active Object: <NombreAObject> *//*-------------------------------------*/
typedef struct <#nombre>Tag {
    QActive super;                                           /**< QHsm base */
    QEQueue <#colaPtr>;	             /**< Instancia de cola de ev diferidos */
    QEvent const *<#colaSto>[3];   /**< Memoria para la cola de ev diferidos */
    <#otros_miembros>;
} <#nombre>;  /* Private */

/*-- Estados -------------------------------------------------------------- */
static QState <#nombreAO>_initial(<#nombreAO> *me, QEvent const *e);

static QState <#nombreAO>_busy(<#nombreAO> *me, QEvent const *e);
    static QState <#nombreAO>_idle(<#nombreAO> *me, QEvent const *e);
    static QState <#nombreAO>_processing(<#nombreAO> *me, QEvent const *e);

/** Instancia de la clase *//*----------------------------------------------*/
static <#nombreAO> the<#nombreAO>;                             /**< Singleton */


/*************************************************************************//**
Instancia estática de evento. 
@note	<Si no hay parámetros, no es necesario publicar la estructura,
		y el cliente no necesita hacer downcasting desde QEvent*>
 ****************************************************************************/
static <#nombre>Evt const <#nombreInstancia> = {<#SEgnAL_UNICA>_SIG, 0};

/*-- Puntero opaco a la instancia de la clase ------------------------------*/
QActive * const ptr<#nombreAO> = (QActive *)&the<#nombreAO>;        /* Public */


/*- Constructor de la clase ------------------------------------------------*/
void <#nombreAO>_ctor(void) 
{
    <#nombreAO> *me = &the<#nombreAO>;    
    QActive_ctor(&me->super, (QStateHandler)&<#nombreAO>_initial);
    QEQueue_init(&me-><#colaPtr>, me-><#colaSto>, Q_DIM(me-><#colaSto>));

    <#inicializar_miembros>
}  /* Public */

/*- Pseudoestado Inicial    ------------------------------------------------*/
static QState <#nombreAO>_initial(<#nombreAO> *me, QEvent const *e) {
	
	/* SUBSCRIPCIONES A EVENTOS PUBLICOS */
    QActive_subscribe((QActive *)me, <#SEGNALx>_SIG);
    QActive_subscribe((QActive *)me, <#SEGNALy>_SIG);
    QActive_subscribe((QActive *)me, <#SEGNALz>_SIG);
	
	return Q_TRAN(&<#nombreAO_idle>);   
}//

/** State: DIFIERE EVENTO   *//*--------------------------------------------*/
static QState <#nombreAO_busy>(<#nombreAO> *me, QEvent const *e) {
	switch (e->sig) {
		case <#SEGNAL_REQUEST>_SIG: {
			if (QEQueue_getNFree(&me-><#cola>) > 0) {    /* can defer? */
				QActive_defer((QActive *)me, &me-><#cola>, e);
			}
			else {
                <#indicar_error>
			}
			return Q_HANDLED();
		}
	}
	return Q_SUPER(&QHsm_top);
}

/** State: RECUPERA EVENTO DIFERIDO   *//*----------------------------------*/
static QState <#nombreAO_idle>(<#nombreAO> *me, QEvent const *e) {
    switch (e->sig) {   
	    case Q_ENTRY_SIG: {
	    	QActive_recall((QActive *)me, &me-><#cola>) != (QEvent*)0) 
	    	return Q_HANDLED();
	    }
	    <...>
    }
    return Q_SUPER(&<#estado_super>);
}//


/*************************************************************************//**
 Driver 
 Esta parte debe llamarse desde la ISR 
 ***************************************************************************/
void <#nombreIsrDriver>(QActive *me)  /* Public */
{
    
	<...>
	<[#Crear_evento_dinamico]>
    QActive_postFIFO(me, (QEvent const*)&<#nombreEvento>);
    
}//


