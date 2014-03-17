//+--------------------------------------------------------------------------+
//|  $Workfile:: ActiveObjectTemplate.h                  $ $Revision:: 2     $
//+--------------------------------------------------------------------------+
//|  $Author:: Marcelo                                                       $
//|  $Modtime:: 20/07/09 10:37p                                              $
//|  $Archive:: /@CODE/SRC/QP2_LEARN/ActiveObjectTemplate.h                  $
//+--------------------------------------------------------------------------+
#ifndef <#header>_H
#define <#header>_H

/*-- Señales ---------------------------------------------------------------*/
#define <#nombreAO>_SIGNALS \
	<#SEGNALa>_SIG, <#SEGNALb>_SIG

#define <#nombreAO>_PRIVATE_SIGNALS 	\
	l_<#SEGNALp>_SIG

/*-- Eventos públicos ------------------------------------------------------*/
#typedef struct <#nombreEvento>EvtTag {
	QEvent super;
	<#otros_miembros>;
	<...>
} <#nombreEvento>Evt; /* Public */


/* Constructor -------------------------------------------------------------*/
void <#nombreAO>_ctor(void);

/* Drivers -----------------------------------------------------------------*/
void <#nombreIsrDriver>(QActive *me); /* Public */

/* Puntero Opaco a instancia static de la clase ----------------------------*/
extern QActive * const ptr<#nombreAO>;              /* puntero al singleton */

#endif 
//

/* Para enviar mensajes:                                                    

Método 1: crear un evento estático y referenciarlo directamente:                   */

    static SWEvt_ const swevt_tick = {SWTICK_SIG, 0} ;
    QFsm_dispatch((QFsm*)me, (QEvent const*)&swevt_tick);                   /*
    
Método 2: crear un nuevo evento en el Pool mediante Q_NEW y copiar 
          el puntero obtenido en la cola del Objeto Activo destinatario:
                                                                            */
    TxRequestEvt *tue = Q_NEW(TxRequestEvt, TXREQUEST_SIG);         /* pool */
    /* Rellenar miembros evento */
    QActive_postFIFO(ptrTxUart, (QEvent*)tue);                     /* queue */
                                                                            /*
Método 3: crear un nuevo evento en el Pool mediante Q_NEW y publicar
          el evento pasando el puntero obtenido al entorno QF : */

    DataReadyEvt *dsrE = Q_NEW(DataReadyEvt, DATAREADY_SIG);
    dsrE->rxString = me->start;                /*  Rellenar miembros evento */
    dsrE->strLen = me->strLen_; 		       /*  Rellenar miembros evento */
    QF_publish((QEvent const *)dsrE);                   /*  Publicar evento 

Método 4: eventos de Timer:

a) Agregar un evento de Timer como miembro del Active Object:               */

        typedef struct DinoTag {
            QActive super;
            QTimeEvt timeEvt;                   
        } Dino;                                                             /*
                
b) En el Constructor del AO, llamar al constructor del Timer:               */

        QTimeEvt_ctor(&me->timeEvt, l_TIMEOUT_SIG);                         /*
        
c) Dentro del estado que lo requiera, armar el timer:                       */

        QTimeEvt_postIn(&me->timeEvt, (QActive *)me, 500);                  /*

d) Capturar el evento dentro del estado que lo requiera:                    */

        case l_TIMEOUT_SIG: {
            ... 
        }//                                                              
