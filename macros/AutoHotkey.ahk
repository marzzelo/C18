SetTitleMatchMode 2 

;--------------
; QUANTUM FRAMEWORK
;--------------
:*:qth::
ToolTip QTimeEvt_: `nqtec{ctor} qted{disarm} qter{rearm} `nqtei{postIn} qtee{postEvery}
SetTimer, RemoveToolTip, 5000
return

:*:qah::
ToolTip QActive_: `nqaf{postFIFO} qal{postLIFO} qas{suscribe} `nqau{unsuscribe} qad{defer} qar{recall}
SetTimer, RemoveToolTip, 5000
return

:*:qhh::
ToolTip QFsm_: `nqfc{ctor} qfi{init} qfd{dispatch} 
SetTimer, RemoveToolTip, 5000
return

:*:qhh::
ToolTip QFsm_: `nqfc{ctor} qfi{init} qfd{dispatch} `nqhc{ctor} qhi{init} qhd{dispatch}
SetTimer, RemoveToolTip, 5000
return

:*:qfh::
ToolTip Q FRAME: `nqfp{publish} qn{Q_NEW}
SetTimer, RemoveToolTip, 5000
return 

RemoveToolTip:
SetTimer, RemoveToolTip, Off
ToolTip
return

:*:qtr::Q_TRAN(&);{Del}{left 2}
:*:qha::Q_HANDLED();{Del}
:*:qsu::Q_SUPER(&QHsm_top);{Del}
:*:qig::Q_IGNORED();{Del}

:*:qen::Q_ENTRY_SIG:
:*:qex::Q_EXIT_SIG:
:*:qin::Q_INIT_SIG:

:*:qtec::QTimeEvt_ctor(&me->tmr???, ???_SIG);{Del}
:*:qted::QTimeEvt_disarm(&me->tmr???);{Del}
:*:qter::QTimeEvt_rearm(&me->tmr???, ??*Q_SEC);{Del}
:*:qtei::QTimeEvt_postIn(&me->tmr???, (QActive *)me, ??*Q_SEC);{Del}{Del}
:*:qtee::QTimeEvt_postEvery(&me->tmr???, (QActive *)me, ??*Q_SEC);{Del}{Del}

:*:qaf::QActive_postFIFO(ptr???, (QEvent *)???evt);{Del}{Del}
:*:qal::QActive_postLIFO(ptr???, (QEvent *)???evt);{Del}{Del}
:*:qas::QActive_subscribe((QActive *)me, ???_SIG);{Del}{Del}
:*:qau::QActive_unsubscribe((QActive *)me, ???_SIG);{Del}{Del}
:*:qad::QActive_defer((QActive *)me, struct QEQueueTag *eq, QEvent const *e);{Del}{Del}
:*:qar::QActive_recall((QActive *)me, struct QEQueueTag *eq);{Del}{Del}

:*:qhc::QHsm_ctor(me_, initial_);{Del}
:*:qhi::QHsm_init(QHsm *me, QEvent const *e);{Del}
:*:qhd::QHsm_dispatch(QHsm *me, QEvent const *e);{Del}

:*:qfc::QFsm_ctor(me_, initial_);{Del}
:*:qfi::QFsm_init(QFsm *me, QEvent const *e);{Del}
:*:qfd::QFsm_dispatch(QFsm *me, QEvent const *e);{Del}

:*:qfp::QF_publish((QEvent *)???evt);{Del}{Del}
:*:qn::Q_NEW(???evtType, ???_SIG);{Del}

;--------------
; HELP BOXES
;--------------
:*:/box::
FileRead, texto, C:\@C18\macros\box.txt
clipboard = %texto%
Send ^v{up}
return

:*:/sbox::
FileRead, texto, C:\@C18\macros\sbox.txt
clipboard = %texto%
Send ^v{up}
return

:*:/dbox::
FileRead, texto, C:\@C18\macros\dbox.txt
clipboard = %texto%
Send ^v{up}
return

:*:+++::
FileRead, texto, C:\@C18\macros\box+.txt
clipboard = %texto%
Send ^v{up}
return

:*:-...::
FileRead, texto, C:\@C18\macros\sep-.txt
clipboard = %texto%
Send ^v
return

:*:=...::
FileRead, texto, C:\@C18\macros\sep=.txt
clipboard = %texto%
Send ^v
return


;--------------
; HEADERS
;--------------
:*:@fn::
FileRead, texto, C:\@C18\macros\@fn.txt
clipboard = %texto%
Send ^v{up}
return

:*:/fn::
FileRead, texto, C:\@C18\macros\fn.txt
clipboard = %texto%
Send ^v{up}
return


:*:/st::
FileRead, texto, C:\@C18\macros\@st.txt
clipboard = %texto%
Send ^v{up}
return

:*:/fi::
FileRead, texto, C:\@C18\macros\@file.txt
clipboard = %texto%
Send ^v{up}
return


:*:/fh::
FileRead, texto, C:\@C18\macros\headerf.txt
clipboard = %texto%
Send ^v{up}
return

:*:/vh::
FileRead, texto, C:\@C18\macros\vssheader.txt
clipboard = %texto%
Send ^v{up}
return

:*:/fd::
FileRead, texto, C:\@C18\macros\fdoc.txt
clipboard = %texto%
Send ^v{up}
return

:*:/byte::
FileRead, texto, C:\@C18\macros\byte.txt
clipboard = %texto%
Send ^v{up}
return

:*:/dot::
FileRead, texto, C:\@C18\macros\dot.txt
clipboard = %texto%
Send ^v
return

;--------------
; C
;--------------
:*:printf::printf((frchar*)"\r\n\r\n");{del 2}{left 7}
:*:/**<::/**<  */{left 3}
:*:/** ::/**  */{left 3}
:*:/* ::/*  */{left 3}
:*:(fr::(frchar*{right}""{left}

:*:{::{{}{enter}{enter}{right}{up}{tab}

:*:u8::uint8_t{space}
:*:u16::uint16_t{space}
:*:u32::uint32_t{space}
:*:i8::int8_t{space}
:*:i16::int16_t{space}
:*:i32::int32_t{space}

:*:#ifd::{#}ifdef{space}
:*:#ifn::{#}ifndef{space}
:*:#en::{#}endif{space}
:*:#de::{#}define{space}
:*:#un::{#}undef{space}
:*:#in::{#}include{space}
:*:case ::case :{enter}{tab}break;{up}{end}{left}



:*:lab.::[label=""];{del}{left 3}

;--------------
; EXTRAS
;--------------
^!r::
WinActivate Docklight V1.6
WinWaitActive Docklight V1.6
SendInput {F5}
WinActivate MPLAB IDE
WinWaitActive MPLAB IDE
SendInput {F9}
WinActivate Docklight V1.6
return



^!m::
run "C:\Program Files\Microchip\MPLAB IDE\Core\MPLAB.exe"
WinWait WINNER2010
run "C:\Program Files\Docklight V1.6\Docklight.exe "C:\@C18\SRC\QP2_LEARN\pic.ptp"
WinWait Docklight V1.6
WinActivate WINNER2010
return



#h::  ; Win+H hotkey
AutoTrim Off  ; Retain any leading and trailing whitespace on the clipboard.
ClipboardOld = %ClipboardAll%
Clipboard =  ; Must start off blank for detection to work.

Send ^c
ClipWait 1
if ErrorLevel  ; ClipWait timed out.
    return

StringReplace, Hotstring, Clipboard, ``, ````, All  ; Do this replacement first to avoid interfering with the others below.
StringReplace, Hotstring, Hotstring, `r`n, ``r, All  ; Using `r works better than `n in MS Word, etc.
StringReplace, Hotstring, Hotstring, `n, ``r, All
StringReplace, Hotstring, Hotstring, %A_Tab%, ``t, All
StringReplace, Hotstring, Hotstring, `;, ```;, All
Clipboard = %ClipboardOld%  ; Restore previous contents of clipboard.

SetTimer, MoveCaret, 10

InputBox, Hotstring, New Hotstring, Type your abreviation at the indicated insertion point. You can also edit the replacement text if you wish.`n`nExample entry: :R:btw`::by the way,,,,,,,, :R:`::%Hotstring%
if ErrorLevel  ; The user pressed Cancel.
    return
IfInString, Hotstring, :R`:::
{
    MsgBox You didn't provide an abbreviation. The hotstring has not been added.
    return
}

FileAppend, `n%Hotstring%, %A_ScriptFullPath%  ; Put a `n at the beginning in case file lacks a blank line at its end.
Reload
Sleep 200  
MsgBox, 4,, The hotstring just added appears to be improperly formatted.  Would you like to open the script for editing? Note that the bad hotstring is at the bottom of the script.
IfMsgBox, Yes, Edit
return

MoveCaret:
IfWinNotActive, New Hotstring
    return

Send {Home}{Right 3}
SetTimer, MoveCaret, Off
return

