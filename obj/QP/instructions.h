/*************************************************************************//**
@page help Creación y Envío de Eventos

@section enviar Enviar mensajes:                                                    

- Método 1: crear un evento estático y referenciarlo directamente:       
@code
    static SWEvt_ const swevt_tick = {SWTICK_SIG, 0} ;
    QFsm_dispatch((QFsm*)me, (QEvent const*)&swevt_tick);                   
@endcode    
- Método 2: crear un nuevo evento en el Pool mediante Q_NEW y copiar 
          el puntero obtenido en la cola del Objeto Activo destinatario:
@code                                                                            
    TxRequestEvt *tue = Q_NEW(TxRequestEvt, TXREQUEST_SIG);         // pool 
    --- Rellenar miembros evento ---
    QActive_postFIFO(ptrTxUart, (QEvent*)tue);                     // queue 
@endcode                                                                            
- Método 3: crear un nuevo evento en el Pool mediante Q_NEW y publicar
          el evento pasando el puntero obtenido al entorno QF : 
@code
    DataReadyEvt *dsrE = Q_NEW(DataReadyEvt, DATAREADY_SIG);
    dsrE->rxString = me->start;                //  Rellenar miembros evento 
    dsrE->strLen = me->strLen_; 		       //  Rellenar miembros evento 
    QF_publish((QEvent const *)dsrE);                   //  Publicar evento 
@endcode


@section sect2 Eventos de Timer:
    -# Agregar un evento de Timer como miembro del Active Object:               
@code
        typedef struct DinoTag {
            QActive super;
            QTimeEvt timeEvt;                   
        } Dino;                                                             
@endcode    
    -# En el Constructor del AO, llamar al constructor del Timer:               
@code
        QTimeEvt_ctor(&me->timeEvt, l_TIMEOUT_SIG);                         
@endcode        
    -# Dentro del estado que lo requiera, armar el timer:                       
@code
        QTimeEvt_postIn(&me->timeEvt, (QActive *)me, 500);                  
@endcode
    -# Capturar el evento dentro del estado que lo requiera:                    
@code
        case l_TIMEOUT_SIG: {
            ... 
        }//                                                                 
@endcode
 ****************************************************************************/
