//;+------------------------------------------------------------------+
//;|       $Workfile:: resources_sp.h             $ $Revision:: 1     $
//;+------------------------------------------------------------------+
//;|         $Author:: Mav                                            $
//;|        $Modtime:: 7/05/11 1:37p                                  $
//;|        $Archive:: /@CODE/SRC/Templates/starter_sets/18F4620/reso $
//;+------------------------------------------------------------------+
 

// S T R I N G S    D E    M E N S A J E S 
#define CHR_YES						'S'
#define CHR_NO						'N'
#define CHR_no						'n'
#define CHR_LINK					'E'
#define CHR_link					'e'
#define CHR_follow					's'
#define CHR_FOLLOW					'S'
#define CHR_alarm					'a'
#define CHR_ALARM					'A'
#define CHR_UNLINK					'n'
#define CHR_DISABLE					'N'
#define CHR_ENABLE					'H'
#define CHR_PERMANENT				'P'
#define CHR_PERIMETRAL				'R'
#define CHR_ZPROGRAMADA				'G'
#define CHR_ZAUX					'X'
#define CHR_ZEMAIL					'E'
#define CHR_ANULLED					'A'
#define CHR_INTERIOR				'I'
#define CHR_QUITAR					'Q'
#define CHR_OUTPUT					'S'
#define CHR_INPUT					'Z'
#define CHR_ACTIVE					'A'	
#define CHR_INACTIVE				'D'	

#define CHR_CONDITIONAL				'C'
#define CHR_ALWAYS					'S'
#define CHR_NEVER					'N'
#define CHR_FLANCO					'F'	
	
#define STR_YES						"SI"	
#define STR_NO						"NO"	


#define TXT_USER_DISABLED			"Usuario inhabilitado"
#define	TXT_UNKNOWN_COMMAND__s		"Comando desconocido: \"%s...\""
#define TXT_AUTHORIZED__s			"Tel %s Autorizado (Principal, ID: 1)"
#define TXT_NO_NEW_USERS_ALLOWED	"Nuevos usuarios no permitidos"
#define TXT_ALREADY_REGD__d			"Usuario ya registrado (ID: %d)"
#define	TXT_MEMORY_FULL				"Memoria Completa"
#define TXT_INCORRECT_NUMBER		"Err: tel incorrecto"
#define TXT_AUTHORIZED__sd			"Tel %s autorizado (ID: %d)"
#define TXT_FWD_HEADER				"REENV: "
#define TXT_ANTENNA_LEVEL__sd		"Nivel de antena: %s (%d)"
#define TXT_VAR_DUMP__				"Mem: %u" \
									"\r\nLlam: %u (Tn:%c,SMS:%c)" \
									"\r\nBat: %s (%d mV) AC:%s" \
									"\r\nTol: %u min" \
									"\r\nP: %s" \
									"\r\nS: %s" \
									"\r\nRec: %u" \
									"\r\nEnv: %u" \
									"\r\nDly: %us"

#define TXT_ZONES__s				"Zonas: (C. %sACTIVADA)"
#define TXT_OUTPUTS					"Salidas:"
#define TXT_LINKS					"Enlaces:\r\nZN:   12345678"
#define TXT_FOLLOWS					"Seguidores:\r\nZN:   12345678"
#define TXT_ERROR_CHECK				"Err: ver(variables,salidas,zonas,enlaces,seguidor,alarmas,hora,email,reenvios,nivel,version,imei)"
#define TXT_USERS					"USUARIOS:\r\n"
#define TXT_USRTOOBIG				"Err: Usr(1..50)"
#define TXT_ERR_SAL_1_8				"Err: Salidas(1..8)"
#define TXT_ERR_NIVEL				"Err: Niveles(1..4)"
#define TXT_ERR_ACCESO				"Err: acc n +-(zon,sal,niv,habil,bat,voz)"
#define TXT_ERR_SAL_1_8_ALIAS		"Err: Salidas(1..8),Alias"
#define TXT_OP_NO_AUT				"Oper. no autorizada"
#define TXT_OUTPUT_TONOFF__sdd		"Salida %s: Ton=%us, Toff=%us"
#define TXT_TONOFF_ERROR			"Err: Tmax=65535 seg"
#define TXT_OUT_LINK_IN__ss			"Enlace salida %s %s Zona %s"
#define TXT_OUT_FOLLOW_IN__ss		"Sigue salida %s %s Zona %s"
#define TXT_ERR_OUT					"Err: sal n (si,no,enl,alias,temp,alarma,bat,camp,estado)"
#define TXT_LINE_FAIL_TOL__s		"Tol. fallo de linea: %s min"
#define TXT_BATT_CANCELLED			"Reportes de fallo de linea cancelados"
#define TXT_ERR_PER_CONS			"Err: Periodo (tol)"
#define TXT_CUSTOM_MSG__ds			"Mens.Pers %d: \"%s\""
#define TXT_MSG_TOOLONG				"Err: Mens máx:31, mín:3 caracts."
#define TXT_ERR_ZONE				"Err: zona n (norm,int,24hr,perim,prog,email,mens)"
#define TXT_ERR_OPC_SN				"Err: Opc(si,no)"

#define TXT_ERR_ZON_1__8_ALIAS		"Err: Zon(1..8),Alias"
#define TXT_ERR_ZON_1__8			"Err: Zon(1..8)"
#define TXT_ARMED__sds				"Central ACTIVADA (%s, %d: %s)"
#define TXT_ARM_INTERIOR			"ACT. INTERIOR"
#define TXT_ARM_PERIMETRAL			"ACT. PERIMETRAL"
#define TXT_ARM_PROGRAMADO			"ACT. PROGRAMADA"
#define TXT_ARM_AUXILIAR			"ACT. AUXILIAR"
#define TXT_FULL_ARMED				"ACTIVACION TOTAL"
#define TXT_DISARMED__ds			"Central DESACTIVADA (%d: %s)"
#define TXT_PART_DISARMED__sds		"Zona %s DESARMADA (%d: %s)"
#define TXT_ERR_KEYWORD				"Err: Clave 3 a 10 car."
#define TXT_KEYWORD_CHGD__ss		"Clave cambiada OK: %s -> %s"

// Mail
#define TXT_MAIL_CONFIRM			"e-mail actualizado"
#define TXT_MAIL_DISABLE			"e-mails cancelados"
#define TXT_MAIL_ENABLE				"e-mails habilitados"
#define TXT_UNCOMPLETE_MAIL			"Formato: email (address) (gateway)"
#define TXT_MAILSETTINGS__sss		"E-MAIL: %s\r\nGATEWAY: %s\r\nSERVER: %s"

// Server
#define TXT_SERVER_CONFIRM			"Server Actualizado: %s"
#define TXT_UNCOMPLETE_SERVER		"Formato: server (telefono)"
#define TXT_SERVER_DISABLE			"Acceso web cancelado"
#define TXT_SERVER_ENABLE			"Acceso web habilitado"

// Timer
#define TXT_TIM_DISABLED			"ENTRADA AUX ANULADA (%d: %s)"
#define TXT_TIM_ENABLED				"ENTRADA AUX HABILITADA (%d: %s)"

// Passwords
#define	TXT_ERR_CLAVE_INC			"Err: Clave incorrecta"
#define TXT_USR_INEXISTENTE__d  	"Usuario %d inexistente"
#define TXT_MODIF_OK 				"Valor modificado Ok"
#define TXT_ERR_PASSWORDS			"Err: cla (pri,sec) old new"

// Captures
#define TXT_CAPTURES				"Palabras a reenviar:"
#define TXT_UNCOMPLETE_COMMAND		"Formato: Reenviar n (Palabra)"
#define TXT_ERR_CAPTURE				"Err: reenviar 1..5"
#define TXT_CAPTURE_CONFIRM__ds		"Reenviar %d --> %s"

// Reports
#define TXT_ERR_REPORTS				"Err: Reportes (si,no)"
#define TXT_REPORT_CONFIRM__c		"Reportes -> %c"
#define TXT_NEW_USERS_ALLOWED		"Nuevos usuarios permitidos"
#define TXT_NEW_USERS_DISALLOWED	"No se permiten nuevos Usuarios"

#define TXT_ALIAS_NOT_FOUND			"Falta alias"
#define TXT_ZALIAS_CONFIRM__ds		"zona %d --> %s"
#define TXT_SALIAS_CONFIRM__ds		"salida %d --> %s"
#define TXT_ERR_ALIAS				"Err: alias (sal,zon)"
#define TXT_ALL_ERASED				"Todos eliminados"
#define TXT_USR_ERASED__d			"Usr %d eliminado"
#define TXT_QUEUE_CLEARED			"Mensajes en curso cancelados"
#define TXT_ERR_FORWARD_NUM			"Formato: Env (nro) \"msg\""
#define TXT_ERR_FORWARD_MSG			"ERR: falta indicar mensaje"
#define TXT_OUTPUT_OFF				"SALIDA DESACTIVADA"
#define TXT_OUTPUT_ON				"SALIDA ACTIVADA"

// Batería y Línea 220
#define TXT_220LINE_FAIL			"FALLO DE LINEA"
#define TXT_220LINE_RESTORE			"RESTAURACION DE LINEA"
#define TXT_ACFAIL					"FALLO"
#define TXT_ACOK					"OK"
#define TXT_LOW_BATTERY				"Bateria Baja: %d mV"
#define TXT_BATTLINK__d				"Bat.Baja --> salida %d"
#define TXT_BATTUNLINK__d			"Bat.Baja -/-> salida %d"
#define TXT_LEVEL_GOOD				"BUENO"
#define TXT_LEVEL_REGULAR			"REGULAR"
#define TXT_LEVEL_LOW				"BAJO"

// Alarmas
#define TXT_ALRM_TITLE				"Alarmas: "
#define TXT_ALRM_UNCOMPLETE			"Formato: Alarma (1..16)(s,n,c,a,d)(hhmm)(lmijvsd)"
#define TXT_ALRM_ERRAL				"Err: Al(1..16)"
#define TXT_ALRM_ERRMODE			"Err: Mode(si,no,act,desact,cancel)"
#define TXT_ALRM_ERRTIME			"Err: Hora(0000..2359)"
#define TXT_ALRM_ERRDOW				"Err: dias(lmijvsd)"
#define TXT_ALRM_CONFIRM__dcd		"Alarma %d(%c) fijada a las %04d hs."
#define TXT_ALRM_UNLINK__sd			"Salida %s <-/- Alarma Nº%d"
#define TXT_ALRM_LINK__sd			"Salida %s <-- Alarma Nº%d"

// Hora
#define	TXT_HORA_FMTERR 			"Err.ej: \"HORA 0930 JUE 120310\""
#define TXT_HORA_OK_sssss			"Hora: %s/%s/20%s %s:%s hs"
#define TXT_HORA_ERR				"Err. en config. hora"
#define TXT_HORAFECHA__us			"Hora: %04u, Fecha: %s"

// Varios
#define TXT_DEFAULT_CUSTOM_MSG		"Apertura Zona $"
#define TXT_DEFAULT_ZALIAS__d		"ZON%d"
#define TXT_DEFAULT_SALIAS__d		"SAL%d"
#define	TXT_ACCESS_MODIFIED			"Acceso %c usuario %d modificado OK"
#define TXT_VCALL_CNCLLD			"Llamada aux inhabilitada"
#define TXT_VCALL_ENABLD			"Llamada aux habilitada"
#define TXT_USER_UNKNOWN__d			"Usuario %d inexistente"
#define TXT_CMDERR					"Error en comando"
#define TXT_DEFAULTERR				"Err: Default (niv 2..4,sal,zon)"
#define TXT_DEFAULTSET				"Acceso default modificado"
#define TXT_SMSENABLED				"SMS Habilitados"
#define TXT_MODE_OK__s				"Modo de listado: %s"
#define TXT_MODE_ERR				"Err: Modos (resumen,detalle)"
#define TXT_AVISO_SONORO			"Aviso Sonoro "
#define TXT_AVISO_SONORO_ACTIVADO	"Activado"
#define TXT_AVISO_SONORO_ANULADO	"Anulado"
#define TXT_IMEI__s					"IMEI: %s"


// S T R I N G S   D E   C O M A N D O S 

#define TXT_PRI				"PRI" // principal
#define TXT_SEC 			"ALT" // alta secundario
#define TXT_VER				"VER" // verificar variables
#define TXT_SAL				"SAL" // salida
#define TXT_ZON				"ZON" // zona
#define TXT_AUD				"AUD" // audio test
#define TXT_ACT				"ACT" // activar
#define TXT_DES				"DES" // desactivar
#define TXT_LIS				"LIS" // listar
#define TXT_ALI				"ALI" // alias
#define TXT_KEY				"REE" // reenviar
#define TXT_ENV				"ENV" // enviar
#define TXT_CLA				"CLA" // clave
#define TXT_REG				"REG" // registro
#define TXT_BOR				"BOR" // borrar
#define TXT_CAN				"CAN" // cancelar
#define TXT_ACC				"ACC" // acceso
#define TXT_REP				"REP" // reporte
#define TXT_VOZ				"LLA" // llamado
#define TXT_PER				"PER" // periodo
#define TXT_RST				"RST" // reset
#define TXT_TIM				"AUX" // llave auxiliar
#define TXT_MAI				"EMA" // e-mail
#define TXT_ALA				"ALA" // alarma
#define TXT_HOR				"HOR" // hora
#define TXT_DEF				"DEF" // defaults
#define TXT_SMS				"SMS" // sms si|no
#define TXT_MOD				"MOD" // modo
#define TXT_GET				"GET" // get dataset 
#define TXT_SER				"SER" // server
#define TXT_AVI				"AVI" // aviso sonoro

/* STRINGS DE PRIMER PARAMETRO */
#define TPAR_ZON			TXT_ZON	// Ver ZONAS
#define TPAR_SAL			TXT_SAL	// Ver SALIDAS
#define TPAR_VAR			"VAR"	// Ver VARIABLES
#define TPAR_ENL			"ENL"	// Ver ENLACES
#define TPAR_EMA			TXT_MAI	// Ver EMAIL
#define TPAR_SEG			"SEG"	// Ver SEGUIDOR
#define TPAR_ALA			TXT_ALA	// Ver ALARMAS
#define TPAR_REE			TXT_KEY
#define TPAR_HOR			TXT_HOR
#define TPAR_NIV			"NIV"
#define TPAR_VER			"VER"	// VER VERSION
#define TPAR_ACTINT			"INT"	// Activar INTERIOR
#define TPAR_ACTPER			"PER"	// Activar PERIMETRAL
#define TPAR_ACTPRO			"PRO"	// Activar PROGRAMADO
#define TPAR_ACTAUX			"AUX"	// Activar AUXILIAR
#define TPAR_ACTANU			"ANU"	// Activar ANULAR ...
#define TPAR_MDSHRT			"RES"	// Modo Resumen
#define TPAR_MDDTLL			"DET"	// Modo Detalle
#define TPAR_IME			"IME"	// VER IMEI

/* STRINGS DE SEGUNDO PARAMETRO */
#define TPAR2_ZNOR			"NOR"		// zona n NORMAL
#define TPAR2_ZINT			TPAR_ACTINT	// zona n INTERIOR
#define TPAR2_ZPER			TPAR_ACTPER	// zona n PERIMETRAL
#define TPAR2_ZPROG			TPAR_ACTPRO	// zona n PROGRAMADA
#define TPAR2_ZAUX			TPAR_ACTAUX	// zona n AUXILIAR
#define TPAR2_Z24HR			"24H"		// zona n 24H
#define TPAR2_ZEMA			TPAR_EMA	// zona n EMAIL
#define TPAR2_ZFLA			"FLA"		// zona n FLANCO ...
#define TPAR2_ZMENS			"MEN"		// zona n MENSAJE ...
#define TPAR2_STEM			"TEM"		// salida m TEMPORIZAR
#define TPAR2_SBAT			"BAT"		// salida m BATTERY
#define TPAR2_SCAM			"CAM"		// salida m CAMPANA
#define TPAR2_SEST			"EST"		// salida m ESTADO	
#define TPAR2_SSEG			TPAR_SEG	// salida m SEGUIR ...
#define TPAR2_SENL			TPAR_ENL	// salida m ENLACE ...
#define TPAR2_SALI			TXT_ALI		// salida m ALIAS ...
#define TPAR2_SALA			TPAR_ALA	// salida m ALARMA ...


